#include "fonction_megiddo.h"

/*
A chaque point est associé une équation linéaire ==> demi plan
dans un premier temps on regarde les points 2 à 2 pour éliminer des
fonctions.
*/
/*Nombre de point paire*/
/*dans un premier temps, le problème est contraint sur l'axe des abscisses y=0*/



/*
Dans cette fonction on tri le tableau de points donné:
on enlève les redondances au niveau des équations
*/
POINT* triAbscisse(POINT tab[],int longueur){
	int i,compteur;
	POINT *resultat=malloc(longueur*sizeof(POINT));
	compteur=0;
	for(i=0;i<longueur;i+=2){
			if(tab[i].x==tab[i+1].x){
				if(auCarre(tab[i].y)<=auCarre(tab[i+1].y)){
					resultat[compteur]= tab[i+1];
					compteur+=1;
					
				}
				else{
					resultat[compteur]=tab[i];
					compteur+=1;
					
				}

			}else{
				resultat[compteur]=tab[i];
				resultat[compteur+1]=tab[i+1];
				compteur+=2;
				
			}
		

	}
	return resultat;
}
/*
Calcul du carre d'un nombre: rend l'affichage plus lisible
*/
double auCarre(double v){
	double carre =2;
	return (pow(v,carre));
}
/*
Calcul des valeurs critiques:
revient à calculer l'intersection des médiatrice [ai;ai+1] avec l'axe y=0
si nombre de point impaire: on rajoute un point qui existe déjà pour avoir des doublets
*/

DOUBLET* tableauValeurCritique(POINT tab[],int longueur){
	int i,j;
	double valeur;
	double epsilon=0.00000001;
	j=0;
		
	if(longueur%2==0){
		DOUBLET *critique=malloc((longueur/2)*sizeof(DOUBLET));

		for(i=0;i<longueur;i+=2){
			valeur=(auCarre(tab[i+1].x)-auCarre(tab[i].x)+auCarre(tab[i+1].y)-auCarre(tab[i].y))/(epsilon+2*((tab[i+1].x)-(tab[i].x)));
			critique[j].mediatrice=valeur;
			critique[j].a=tab[i];
			critique[j].b=tab[i+1];
			j+=1;
		}
		return critique;

	}
	else{
		longueur+=1;
		DOUBLET *critique=malloc((longueur/2)*sizeof(double));

		for(i=0;i<longueur-1;i+=2){
			valeur=(auCarre(tab[i+1].x)-auCarre(tab[i].x)+auCarre(tab[i+1].y)-auCarre(tab[i].y))/(epsilon+2*((tab[i+1].x)-(tab[i].x)));
			critique[j].mediatrice=valeur;
			critique[j].a=tab[i];
			critique[j].b=tab[i+1];
			j+=1;
	}
		critique[longueur].mediatrice=critique[0].mediatrice;
		critique[longueur].a=critique[0].a;
		critique[longueur].b=critique[0].b;
		return critique;
	}
	
	

}


