#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structures.h"

POINT first_point;		/* first hull POINT pour le calcul de l'enveloppe convexe*/

double min(double a, double b){
	if(a<b)
		return a;
	else return b;
}

double max(double a, double b){
	if(a>b)
		return a;
	else return b;
}

/**
 * calcule la distance entre les points a et b
**/
double distance(POINT a, POINT b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double signed_triangle_area(POINT a, POINT b, POINT c)
{
	return( (a.x*b.y - a.y*b.x + a.y*c.x 
		- a.x*c.y + b.x*c.y - c.x*b.y) / 2.0 );
}

double triangle_area(POINT a, POINT b, POINT c)
{
	return( fabs(signed_triangle_area(a,b,c)) );
}

bool ccw(POINT a, POINT b, POINT c)
{
	double signed_triangle_area();

	return (signed_triangle_area(a,b,c) > EPSILON);
}

bool cw(POINT a, POINT b, POINT c)
{
	double signed_triangle_area();

	return (signed_triangle_area(a,b,c) < - EPSILON);
}

bool collinear(POINT a, POINT b, POINT c)
{
	double signed_triangle_area();

	return (fabs(signed_triangle_area(a,b,c)) <= EPSILON);
}

void print_points(POINT p[], int n)
{
        int i;                  /* counter */

        for (i=0; i<n; i++)
                printf("(%lf,%lf)\n",p[i].x,p[i].y);
}

void print_point(POINT* p)
{
	printf("%f %f\n",p->x,p->y);
}

void print_polygon(polygon *p)
{
	int i;			/* counter */

        for (i=0; i<p->n; i++)
                //printf("(%f,%f)\n",(p->p[i]).x,(p->p[i]).y);
        	print_point(&p->p[i]);
}






void sort_and_remove_duplicates(POINT in[], int *n)
{
        int i;                  /* counter */
        int oldn;               /* number of points before deletion */
        int hole;               /* index marked for potential deletion */
	bool leftlower();

	qsort(in, *n, sizeof(POINT), leftlower);

        oldn = *n;
	hole = 1;
        for (i=1; i<oldn; i++) {
		if ((in[hole-1].x == in[i].x) && (in[hole-1].y == in[i].y)) 
                        (*n)--;
                else {
                		in[hole].x = in[i].x;
                		in[hole].y = in[i].y;
                        hole = hole + 1;
                }
        }
        in[hole].x = in[oldn-1].x;
        in[hole].y = in[oldn-1].y;
}







void convex_hull(POINT in[], int n, polygon *hull)
{
	int i;			/* input counter */
	int top;		/* current hull size */
	bool smaller_angle();
	
	if (n <= 3) { 		/* all points on hull! */
		for (i=0; i<n; i++)
			(hull->p[i]).x = in[i].x;
			(hull->p[i]).y = in[i].y;
		hull->n = n;
		return;
	}

	sort_and_remove_duplicates(in,&n);
	first_point.x = in[0].x;
	first_point.y = in[0].y;


	qsort(&in[1], n-1, sizeof(POINT), smaller_angle);

	(hull->p[0]).x = first_point.x;
	(hull->p[0]).y = first_point.y;


	(hull->p[1]).x = in[1].x;
	(hull->p[1]).y = in[1].y;

	/* sentinel to avoid special case */
	in[n].x = first_point.x;
	in[n].y = first_point.y;

	top = 1;
	i = 2;

	while (i <= n) {
		if (!ccw(hull->p[top-1], hull->p[top], in[i])) 
			top = top-1;	/* top not on hull */
		else {
			top = top+1;
                    	//copy_point(in[i],hull->p[top]);
			(hull->p[top]).x= in[i].x;
			(hull->p[top]).y= in[i].y;
			i = i+1;
		}
	}

	hull->n = top;
}


bool leftlower(POINT *p1, POINT *p2)
{
	if ((*p1).x < (*p2).x) return (-1);
	if ((*p1).x > (*p2).x) return (1);

        if ((*p1).y < (*p2).y) return (-1);
        if ((*p1).y > (*p2).y) return (1);

	return(0);
}

bool smaller_angle(POINT *p1, POINT *p2)
{
	if (collinear(first_point,*p1,*p2)) {
		if (distance(first_point,*p1) <= distance(first_point,*p2))
			return(-1);
		else
			return(1);
	}

	if (ccw(first_point,*p1,*p2))
		return(-1);
	else
		return(1);
}






/**
 * Teste si deux cercles c1 et c2 sont égaux
**/
int estEgal( CERCLE c1, CERCLE c2 ){
    if( (c1.x == c2.x) && (c1.y == c2.y) && (c1.d == c2.d) )
        return 1;
    else
        return 0;
}



/**
 * Teste si les points du tableau sont alignes
 * retourne 1 si oui, 0 sinon
**/
int pointsColineaires(POINT T[], int nbPoints){
	POINT a = T[0];
	int i=1;
	while(distance(a,T[i])==0.0 && i<nbPoints)
		i++;
	POINT b = T[i];
	while(T[i].x!=0 && T[i].y!=0 && i<nbPoints){
		if( (T[i].y-a.y)/(b.y-a.y) != (T[i].x-a.x)/(b.x-a.x))
			return 0;
	}
	
	return 1;
}



/**
 * calcule le determinant (avec la regle du Sarrus):
 * | a.x  b.x  c.x |
 * | a.y  b.y  c.y |
 * |  1    1    1  |
**/
double calculer_determinant3(POINT a, POINT b, POINT c){
	return a.x*b.y + a.y*c.x + b.x*c.y - b.y*c.x - a.y*b.x - a.x*c.y;
}

/**
 * calcule le determinant:
 * | a.x  b.x |
 * | a.y  b.y |
**/
double calculer_determinant2(POINT a, POINT b){
	return a.x*b.y - a.y*b.x;
}

//retourne l'index d'un POINT avec des coeffs negatifs dans l'ecriture p = alpha*T[i] + betha*T[j]
//on utilise Cramer pour un systeme de dimension 2
int coefficients_negatifs(POINT p,POINT T[], int nbPoints){
	int alpha;
	int betha;
	for(int i=0; i<nbPoints-1;i++){
		for(int j=i+1;j<nbPoints;j++){
			if(calculer_determinant2(T[i],T[j])!=0){
				alpha=calculer_determinant2(p,T[j])/calculer_determinant2(T[i],T[j]);
				if(alpha<0) 
					return i;
				else{
					betha=calculer_determinant2(T[i],p)/calculer_determinant2(T[i],T[j]);
					if(betha<0) 
						return j;
				}
			}
		}
	}
	return -1;
}

//retourne 1 si p appartient a conv(T), 0 sinon
int appartenance_conv(POINT p,POINT T[], int nbPoints){
	
	//TODO
	return 1;
}

//retourne 1 si p appartient a aff(T), 0 sinon
int appartenance_aff(POINT p,POINT T[], int nbPoints){
	int i=0;
	while(T[i].x!=0 && T[i].y!=0)
		i++;
	//si on a un seul point, il faut que p et T[0] coincident pour que p appartienne a aff(T)
	if(i==1 && distance(p,T[i])!=0)
		return 0;
	else if(i==1 && distance(p,T[i])==0)
		return 0;
	//si les POINT de T sont allignes, il faut que p appartienne a la droite pour qu'il appartienne a aff(T)
	else if(pointsColineaires(T,nbPoints)){
		POINT temp[nbPoints+1];
		temp[0] = p;
		for(int j=1;j<=nbPoints;j++)
			temp[j]=T[j-1];
		if(pointsColineaires(temp,nbPoints+1))
			return 1;
		else return 0;
	} 
	//si les points de sont pas allignes, l'espace affine c'est tout le plan et donc p y appartienne
	else return 1;
}

//on efface du tableau T un element qui a des coeffs negatifs dans la decomposition c = coeff[i]*T[i]
void dropping(POINT c,POINT T[], int nbPoints){
	int index = coefficients_negatifs(c, T, nbPoints);
	if(index == -1){
		printf("erreur: pas des coeffs negatifs pour le dropping");
		exit(-1);
	}
	for(int i=index;i<nbPoints-1;i++)
		T[i]=T[i+1];
	T[nbPoints-1].x = 0;
	T[nbPoints-1].y = 0;
}

void walking(POINT* c, POINT T[], int nbPoints){
	//TODO deplace c vers cc(T)

}


CERCLE algorithme_fischer(POINT S[], int nbPoints){

	POINT c = S[0];

	printf("in function c.x = %f c.y = %f\n", c.x, c.y); 

	POINT p; // le POINT le plus eloigne de c
	double max=0;
	for(int i=1; i<nbPoints;i++)
    {
    	POINT q = S[i];
    	printf("in function q.x = %f q.y = %f\n", q.x, q.y);
    	if(max < distance(c,q)){
    		max = distance(c,q);
    		p = q;
    	}
    }

	POINT T[3]={};
	T[0] = p;

	while(!appartenance_conv(c,T,3)){
		if(appartenance_aff(c,T,3)){
			dropping(c,T,3);
		}
		walking(&c, T,3);
	}

	CERCLE resultat;
	resultat.x = c.x;
	resultat.y = c.y;
	resultat.d = 2*distance(c,p);
	return resultat;
}
