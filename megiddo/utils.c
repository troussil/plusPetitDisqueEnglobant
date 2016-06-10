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