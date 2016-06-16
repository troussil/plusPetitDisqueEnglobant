
#include "solution_brute_contrainte.h"





CERCLE* solutionBruteContrainte(POINT tab[],int Nbpoint,double yc){
	CERCLE *unPoint=malloc(sizeof(CERCLE));
	CERCLE *deuxPoint=malloc(sizeof(CERCLE));
	CERCLE *englobant=malloc(sizeof(CERCLE));
	unPoint=ensembleUnPoint(tab,Nbpoint,yc);
	deuxPoint=ensembleDeuxPoints(tab,Nbpoint,yc);
	if((unPoint->d)<(deuxPoint->d)){
		*englobant=*unPoint;
	}else{
		*englobant=*deuxPoint;
	}
return englobant;

}

TABPOINT* compteurCercle(CERCLE c,POINT tab[],int longueur){
	POINT *enveloppeConvexe=malloc(longueur*sizeof(POINT));
	TABPOINT *tableau =malloc(sizeof(TABPOINT));
	double epsilon=0.0000001;
	int i;
	int compteur=0;
	for(i=0;i<longueur;i++){
		if(fabs((distance(tab[i],c.centre)-c.d))<=epsilon){
			enveloppeConvexe[compteur]=tab[i];
			compteur+=1;
		}
	}
	tableau->longueur=compteur;
	tableau->t= enveloppeConvexe;
	return tableau;
}

CERCLE* ensembleUnPoint(POINT tab[],int Nbpoint,double yc){
	int i;
	int j;
	int faux;
	double rayonMinimum=2000000;
	CERCLE *temp=malloc(sizeof(CERCLE));
	CERCLE *englobant=malloc(sizeof(CERCLE));
	englobant->centre.x=0;
	englobant->centre.y=0;
	englobant->d=2000000;

	for(i=0;i<Nbpoint;i++){
		faux=0;
		temp->centre.x=tab[i].x;
		temp->centre.y=yc;
		temp->d=sqrt(auCarre((tab[i].y)-yc));

		for(j=0;j<Nbpoint;j++){
			if(estContenuCercle(*temp,tab[j])==0){
				faux=1;
				break;
			}
			
		}
		if((faux==0)&&((temp->d)<rayonMinimum)){
			*englobant=*temp;
			// printf("1 points: plus petit cercle minimum: point %d, centre (%lf,%lf), rayon %lf\n",i,englobant->centre.x,englobant->centre.y,englobant->d );
			rayonMinimum=englobant->d;
		}
	}
	return englobant;
}

CERCLE* ensembleDeuxPoints(POINT tab[], int taille, double yc){
	//int Nbpoint=triAbscisseEgales(tab,taille);//élimine les points de même abscisses
	int Nbpoint=taille;
	int i;
	int j;
	int k;
	int faux;
	double valeur_en_zero;
	double coeff_directeur;
	double valeur;
	double epsilon=0.00000001;
	double rayonMinimum=2000000;
	CERCLE *temp=malloc(sizeof(CERCLE));
	CERCLE *englobant=malloc(sizeof(CERCLE));
	
	for(i=0;i<Nbpoint;i++){
		for(j=0;j<Nbpoint;j++){
			if(i!=j){
				if(tab[i].x!=tab[j].x){
					faux=0;
					valeur_en_zero=(auCarre(tab[j].x)-auCarre(tab[i].x)+auCarre(tab[j].y)-auCarre(tab[i].y))/(epsilon+2*((tab[j].x)-(tab[i].x)));
					coeff_directeur=(((tab[j].y)-(tab[i].y))/((tab[i].x)-(tab[j].x)));
					valeur=valeur_en_zero+ (coeff_directeur*yc);
					temp->centre.x=valeur;
					temp->centre.y=yc;
					temp->d=distance(temp->centre,tab[j]);
					// printf("2 Points: cercle minimum: point {%d,%d}, centre (%lf,%lf), rayon %lf\n",i,j,temp->centre.x,temp->centre.y,temp->d );

					for(k=0;k<Nbpoint;k++){

						if(estContenuCercle(*temp,tab[k])==0){
							faux=1;
							break;
						}	
					}

					if((faux==0)&&((temp->d)<rayonMinimum)){
						*englobant=*temp;
						// printf("2 Points: plus petit cercle minimum: point %d,%d, centre (%lf,%lf), rayon %lf\n",i,j,englobant->centre.x,englobant->centre.y,englobant->d );

						rayonMinimum=englobant->d;
					}
					faux=0;
				}
			}

		}
	}
	return englobant;
}


int estContenuCercle(CERCLE c,POINT a){
	double epsilon=0.000001;
	if(distance(c.centre,a)<=(c.d)+epsilon){
		// printf("le point (%lf,%lf) est contenu dans C(%lf,%lf,%lf)\n",a.x,a.y,c.centre.x,c.centre.y,c.d );
		// printf("distance a->c=%lf\n",distance(c.centre,a) );
		return 1;
	}
	else{
		// printf("le point (%lf,%lf) n'est pas contenu dans C(%lf,%lf,%lf)\n",a.x,a.y,c.centre.x,c.centre.y,c.d );
		// printf("distance a->c=%lf\n",distance(c.centre,a) );
		return 0;
	}
}


// int main(){

// 	POINT tab[8] = {{-3,-1},{-2,4},{1,1},{2,2},{3,3},{0,0},{3.133918,2},{0,6}};	
// 	CERCLE *c=malloc(sizeof(CERCLE));
// 	TABPOINT* tabpoint=malloc(sizeof(TABPOINT));
// 	c=solutionBruteContrainte(tab,8,0);
// 	printf("solution: cercle c de centre x=%lf y=%lf et de rayon %lf\n",c->centre.x,c->centre.y,c->d );
// 	 tabpoint=compteurCercle(*c,tab,8);
// 	 afficherTableauPoint(tabpoint->t,tabpoint->longueur);


// }