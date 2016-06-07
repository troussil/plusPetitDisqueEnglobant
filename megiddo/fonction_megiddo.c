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
int triAbscisse(POINT tab[],int longueur){
	int i,j,k,compteur,doublon,c;
	POINT *resultat=malloc(longueur*sizeof(POINT));
	compteur=0;
	doublon=0;
	for(i=0;i<longueur;i+=2){//on prend les points 2 par 2
			if(tab[i].x==tab[i+1].x){//si ils ont la même abscisse
				if(auCarre(tab[i].y)<=auCarre(tab[i+1].y)){
					resultat[compteur]= tab[i+1];
					i-=1;
					compteur+=1;
					//on supprime le plus proche de (x,0)
				}
				else{
					resultat[compteur]=tab[i];
					compteur+=1;
					
				}
				doublon+=1;

			}else{
				resultat[compteur]=tab[i];
				resultat[compteur+1]=tab[i+1];
				compteur+=2;
				
			}
		printf("%d doublon\n",doublon);


	}
	POINT *resultat_without_zero=malloc((longueur-doublon)*sizeof(POINT));
	c=0;
	for (j = 0; j < longueur; j++){
		if((resultat[j].x==resultat[j+1].x)&&(resultat[j].y==resultat[j+1].y)){
			j+=1;
		}
		resultat_without_zero[c]=resultat[j];
		c+=1;
	}
	for(k=0;k<longueur-doublon;k++){
		tab[k]=resultat_without_zero[k];
	}
	return longueur-doublon;

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

/*
Calcul la position de x* la solution par rapport à xm
*/

int calculPositionSolution(POINT tab[],int longueur,double mediane){
	int i;
	double max[2];
	POINT *xm=malloc(sizeof(POINT));
	xm->x=mediane;
	xm->y=0;
	max[0]=0;// xm<x*
	max[1]=0;// xm>x*
	for(i=0;i<longueur;i++){
		if((distance(*xm,tab[i])>=max[0])||(distance(*xm,tab[i])>=max[1])){

			if((tab[i].x)<(xm->x)){

				max[0]=distance(*xm,tab[i]);
			}else{

				max[1]=distance(*xm,tab[i]);
			}

		}

	}
	if(max[0]>max[1]){

		return INFERIEUR;

	}
	else if(max[0]<max[1]){

		return SUPERIEUR;

	}
	else{

		return EGAL;
	}

}
/*
on regarde les xcritique > ou < à xm
on peut enlever 1/2 de ces points
*/

int pruning(POINT point[],int longueur){
	int i,j,compteur,solution,taille;
	double med;
	compteur=0;
	/*Tableau de départ*/
	printf("tabeau de point de départ\n");
	afficherTableauPoint(point,longueur);

	/*Trie de doublets de même abscisse*/
	taille=triAbscisse(point,longueur);
	printf("abscisse trié: \n");
	afficherTableauPoint(point,taille);

	/*Calcul des valeurs critiques*/
	if(taille%2!=0)
		taille+=1;
	DOUBLET* doublet=malloc(taille/2*sizeof(DOUBLET));
	doublet=tableauValeurCritique(point,taille);
	printf("Calcul des valeurs critiques: \n");
	afficherTableauDoublet(doublet,taille/2);

	/*Trie des valeurs pour trouver la médiane + gestion des cas impairs*/
	quickSortDoublet(doublet,0,taille/2-1);
	printf("tableau de doublets trié pour trouver la médiane\n");
	afficherTableauDoublet(doublet,taille/2);
	med=mediane(doublet,taille/2);
	printf("valeur médiane: %lf\n",med );


	/*Création d'un POINT médian (xm,0)*/
	POINT *xm=malloc(sizeof(POINT));
	xm->x=med;
	xm->y=0;

	/*Calcul de la position de x*
	=2 fin
	=1 xm<x*
	=0 xm>x*
	 */
	solution=calculPositionSolution(point,taille,xm->x);
	if(solution==1){
		printf("xm<x*\n");
	}
	else{
		printf("xm>x*\n");
	}

	/*élagage de 1/4 des points*/
	POINT *result=malloc(((int)(3*taille/4)+1)*sizeof(POINT));//resultat
	POINT *elim=malloc(((int)(taille/4)+1)*sizeof(POINT));//point à éliminer

	for(i=0;i<((int)(taille/4)+1);i++){
		if(solution==1){
			if(doublet[i].mediatrice<=(xm->x)){
				elim[i]=*distanceInf(*xm,&doublet[i].a,&doublet[i].b);
			}
		}
		else if(solution==0){

			if(doublet[i].mediatrice>=(xm->x)){
				elim[i]=*distanceInf(*xm,&doublet[i].a,&doublet[i].b);
			}

		}
		else{
			exit(EXIT_SUCCESS);
		}
	}
	printf("valeurs à éliminer:\n");
	afficherTableauPoint(elim,(int)(taille/4)+1);
	quickSortPoint(elim,0,((int)(taille/4)));
	quickSortPoint(point,0,taille-1);

	for(j=0;j<taille;j++){
		if((point[j].x==elim[compteur].x)&&(point[j].y==elim[compteur].y)){
			compteur++;

		}else{
			result[j-compteur]=point[j];
		}
			
	}
	for(j=0;j<((int)(3*taille/4)+1);j++){
		point[j]=result[j];
	}
	return taille-compteur;		
}





