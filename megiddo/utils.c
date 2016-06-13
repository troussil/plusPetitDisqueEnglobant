#include "utils.h"


/*
Calcul du carre d'un nombre: rend l'affichage plus lisible
*/
double auCarre(double v){
	double carre =2;
	return (pow(v,carre));
}

/*
Calcul la distance entre 2 points
*/
double distance(POINT a , POINT b){
	double norme;
	norme=sqrt(auCarre((a.x)-(b.x))+auCarre((a.y)-(b.y)));
	return norme;
}

POINT* distanceInf(POINT xm, POINT *a, POINT *b){
	double normeA,normeB;
	normeA=sqrt(auCarre((xm.x)-(a->x))+auCarre((xm.y)-(a->y)));
	normeB=sqrt(auCarre((xm.x)-(b->x))+auCarre((xm.y)-(b->y)));
	if(normeA>=normeB)
		return b;
	else
		return a;

}
int partiEntiere(int a){
	return (int)a;
}
void calculDroite(DOUBLET tab[],int longueur){
	int i;
	double coeffDirecteur;
	double ordonneOrigine;
	for (i = 0; i < longueur; i++){
		ordonneOrigine=((((tab[i].a.y)*(tab[i].b.x))-((tab[i].b.y)*(tab[i].a.x)))/((tab[i].b.x)-(tab[i].a.x)));
		coeffDirecteur=((tab[i].a.y)-ordonneOrigine)/(tab[i].a.x);
		tab[i].droite.p=ordonneOrigine;
		tab[i].droite.m=coeffDirecteur;
	}
}
int estParallele(DOUBLET d1, DOUBLET d2){
	if((d1.droite.m)==(d2.droite.m)){
		return 1;
	}
	else{
		return 2;
	}
}
POINT* calculIntersection(DOUBLET d1, DOUBLET d2){
	double abscisse;
	double ordonne;
	POINT *intersection = malloc(sizeof(POINT));
	abscisse=((d2.droite.p)-(d1.droite.p))/((d1.droite.m)-(d2.droite.m));
	ordonne=((d1.droite.m)*abscisse)+(d1.droite.p);
	intersection->x= abscisse;
	intersection->y=ordonne;
}