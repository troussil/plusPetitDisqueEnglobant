#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "structures.h"

POINT first_point;		/* first hull POINT pour le calcul de l'enveloppe convexe*/

void print_point(POINT* p)
{
	printf("%f %f\n",p->x,p->y);
}


void print_polygon(polygon *p)
{
	int i;
	for (i=0; i<p->n; i++)
    	print_point(&p->p[i]);
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



int ccw(POINT a, POINT b, POINT c)
{
	double signed_triangle_area();

	return (signed_triangle_area(a,b,c) > EPSILON);
}

int cw(POINT a, POINT b, POINT c)
{
	double signed_triangle_area();

	return (signed_triangle_area(a,b,c) < - EPSILON);
}


/**
 * verifie si a,b,c alignes
**/
int collinear(POINT a, POINT b, POINT c)
{
	double signed_triangle_area();

	return (fabs(signed_triangle_area(a,b,c)) <= EPSILON);
}

/**
 * Teste si les points du tableau sont alignes
 * retourne 1 si oui, 0 sinon
**/
int tableau_collinear(POINT T[], int nbPoints){
	POINT a = T[0];
	POINT b = T[1];
	int i=2;
	
	while(i<nbPoints){
		if(!collinear(a,b,T[i]))
			return 0;
		i++;
	}
	
	return 1;
}

/**
 * tri des points et enlevement des dupliques
**/
void sort_and_remove_duplicates(POINT in[], int *n)
{
    int i;                  /* counter */
    int oldn;               /* number of points before deletion */
    int hole;               /* index marked for potential deletion */
	int leftlower();

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


/**
 * calcule l'enveloppe convexe grace a l'algorithme de Graham
**/
void convex_hull(POINT in[], int n, polygon *hull)
{
	int i;			/* input counter */
	int top;		/* current hull size */
	int smaller_angle();
	
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

	if(tableau_collinear(in,n)){
		hull->n = 2;
		hull->p[0]=in[0];
		hull->p[1]=in[n-1];
	}
	else{

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
			(hull->p[top]).x= in[i].x;
			(hull->p[top]).y= in[i].y;
			i = i+1;
		}
	}

	hull->n = top;
}
}


int leftlower(POINT *p1, POINT *p2)
{
	if ((*p1).x < (*p2).x) return (-1);
	if ((*p1).x > (*p2).x) return (1);

    if ((*p1).y < (*p2).y) return (-1);
    if ((*p1).y > (*p2).y) return (1);

	return(0);
}

int smaller_angle(POINT *p1, POINT *p2)
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

void init_tab(POINT tab[], int nbPoints){
	int i;
	for(i=0;i<nbPoints;i++){
		tab[i].x=0;
		tab[i].y=0;
	}
}

int equals_zero(POINT p){
	//printf("Dans equals zero: %f %f \n", p.x, p.y);
	if(p.x != 0.0 || p.y != 0.0){
		
		return (0);
	}
	else{
		printf("je suis ici \n");
		return (1);
	}
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
	int i;
	for(i=0; i<nbPoints-1;i++){
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
// calcule l'enveloppe convexe de T et celui te T+p et verifie si c'est le meme
int appartenance_conv(POINT p,POINT T[], int nbPoints){
	
    polygon initial;
    polygon a_comparer;

	POINT tab_initial[nbPoints];
	POINT tab_a_comparer[nbPoints];

	int i;

	while(T[i].x != 0 && T[i].y !=0){
		tab_initial[i]=T[i];
		tab_a_comparer[i]=T[i];
		//printf("%f rt %f\n", tab_a_comparer[i].x,tab_a_comparer[i].y);
		i++;
	}
	tab_a_comparer[i]=p;
	//printf("%f rt %f\n", tab_a_comparer[i].x,tab_a_comparer[i].y);

    convex_hull(tab_initial,i,&initial);
    convex_hull(tab_a_comparer,i+1,&a_comparer);

    //printf("\npolygine initial: \n");
    //print_polygon(&initial);
    //printf("\npolygine a comparer: \n");
    //print_polygon(&a_comparer);

    if(initial.n != a_comparer.n)
    	return 0;
    else{
    	for (i=0; i<initial.n; i++)
            if(distance(initial.p[i],a_comparer.p[i])!=0)
        		return 0;
    }

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
	else if(tableau_collinear(T,nbPoints)){
		POINT temp[nbPoints+1];
		temp[0] = p;
		for(int j=1;j<=nbPoints;j++)
			temp[j]=T[j-1];
		if(tableau_collinear(temp,nbPoints+1))
			return 1;
		else return 0;
	} 
	//si les points de sont pas allignes, l'espace affine c'est tout le plan et donc p y appartienne
	else return 1;
}

//on efface du tableau T un element qui a des coeffs negatifs dans la decomposition c = coeff[i]*T[i]
void dropping(POINT c,POINT T[], int nbPoints){
	int i;
	int index = coefficients_negatifs(c, T, nbPoints);
	if(index == -1){
		printf("erreur: pas des coeffs negatifs pour le dropping");
		exit(-1);
	}
	for(i=index;i<nbPoints-1;i++)
		T[i]=T[i+1];
	T[nbPoints-1].x = 0;
	T[nbPoints-1].y = 0;
}

int not_in(POINT tab[], POINT element, int nbPoints){
	int i;
	for(i=0;i<nbPoints;i++)
		if(tab[i].x == element.x && tab[i].y == element.y)
			return 0;
	return 1;
}

//Renvoie le cercle le plus petit passant par deux points p1 et p2
CERCLE cerclePassantParDeuxPoints( POINT p1 , POINT p2){
	
	CERCLE c;
		
	c.x = (p1.x + p2.x)/2;
	c.y = (p1.y + p2.y)/2;
	c.d = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	
	return c;	
}


//Renvoie le cercle le plus petit passant par trois points p1, p2, et p3
CERCLE cerclePassantParTroisPoints( POINT p1 , POINT p2 , POINT p3){
	
	CERCLE c;

	float det =  (p1.x - p2.x) * (p2.y - p3.y) - (p2.x - p3.x)* (p1.y - p2.y); 

    	if (det == 0) { 
		c.d = 100000000000; 
		c.x = 0; 
		c.y=0; 

	} else {
		int offset = pow(p2.x,2) + pow(p2.y,2);
    		int bc =   ( pow(p1.x,2) + pow(p1.y,2) - offset )/2.0;
    		int cd =   (offset - pow(p3.x, 2) - pow(p3.y, 2))/2.0;

	    	c.x =  (bc * (p2.y - p3.y) - cd * (p1.y - p2.y)) / det;
	    	c.y =  (cd * (p1.x - p2.x) - bc * (p2.x - p3.x)) / det;
	    	c.d = 2 * sqrt( pow(p2.x - c.x,2) + pow(p2.y-c.y,2));
	}
	return c;	
}

CERCLE algorithme_fischer(POINT S[], int nbPoints){

	polygon enveloppe_convexe;
	POINT maxP; //le point le plus proche du cercle
	POINT circumcentre; // cc(T)
	double diametre;
	int i,j,ok;
	double max=0;

	sort_and_remove_duplicates(S,&nbPoints);

	POINT c = S[0];
	POINT p; // le POINT le plus eloigne de c
	
	for(i=1; i<nbPoints;i++)
    {
    	POINT q = S[i];
    	if(max < distance(c,q)){
    		max = distance(c,q);
    		p = q;
    	}
    }

	POINT T[3];
	init_tab(T,3);
	T[0] = p;

	POINT S_moins_T[nbPoints-1];
	printf("nbr de points dans S moins T: %d\n", nbPoints);

	while(!appartenance_conv(c,T,3)){

		printf("le point c est: %f %f\n", c.x,c.y);

		printf("dans T on a:\n");
		for(i=0;i<3;i++)
			printf("%f %f\n", T[i].x, T[i].y);

		if(appartenance_aff(c,T,3)){
			dropping(c,T,3);
		}


		/* Calcul du circumcentre cc(T) et diametre du cercle engeindre par T*/

		i=0;

		while(T[i].x != 0 || T[i].y != 0)
			i++;

		if(i==1){
			printf("circumcentre T[0] %f %f\n", T[0].x, T[0].y);
			circumcentre = T[0];
			diametre = 0;
		}
		else if(i==2){
			printf("on calcule le circumcentre a partir de 2 points %f %f et %f %f \n", T[0].x, T[0].y, T[1].x, T[1].y);
			circumcentre.x = cerclePassantParDeuxPoints(T[0],T[1]).x;
			circumcentre.y = cerclePassantParDeuxPoints(T[0],T[1]).y;
			diametre = cerclePassantParDeuxPoints(T[0],T[1]).d;
			printf("cc.x = %f; cc.y =  %f; c.d = %f \n", circumcentre.x, circumcentre.y, diametre);
		} else {
			printf("on calcule le circumcentre a partir de 3 points %f %f, %f %f et %f %f \n", T[0].x, T[0].y, T[1].x, T[1].y, T[2].x, T[2].y);
			if(cerclePassantParTroisPoints(T[0],T[1],T[2]).d!=100000000000){
				circumcentre.x = cerclePassantParTroisPoints(T[0],T[1],T[2]).x;
				circumcentre.y = cerclePassantParTroisPoints(T[0],T[1],T[2]).y;
				diametre = cerclePassantParTroisPoints(T[0],T[1],T[2]).d;
				printf("cc.x = %f; cc.y =  %f; c.d = %f \n", circumcentre.x, circumcentre.y, diametre);
			}
			else
				printf("impossible calculer circumcentre, points colineaires\n");
		}


		/* Calcul du tableau S\T */

		j=0;
		ok=0;
		init_tab(S_moins_T, nbPoints-1);
		printf("points de S moins T:\n");
		for(i=0; i<nbPoints; i++){
			if(not_in(T,S[i],3)) {
				S_moins_T[j]=S[i];

				if(distance(S_moins_T[j],circumcentre) > diametre/2)
					ok=1;

				j++;
			}

		}

		//printf("j = %d\n",j);


		if(ok){
			i=0;
			while(!equals_zero(S_moins_T[i])){
				printf("%f %f et equalsZero = %d \n", S_moins_T[i].x, S_moins_T[i].y, equals_zero(S_moins_T[i]));
				i++;
			}

			printf("j = %d\n",i);

			convex_hull(S_moins_T, i+1, &enveloppe_convexe);
			printf("enveloppe convexe de S moins T: \n");
			print_polygon(&enveloppe_convexe);
			max=0;
			for(i=0;i<enveloppe_convexe.n;i++){
				if(distance(c,enveloppe_convexe.p[i])>max){
					max = distance(c,enveloppe_convexe.p[i]);
					maxP.x = (enveloppe_convexe.p[i]).x;
					maxP.y = (enveloppe_convexe.p[i]).y;
				}
			}

			i=0;
			while((T[i].x != 0 || T[i].y != 0) && i<3)
				i++;
			T[i].x = maxP.x;
			T[i].y = maxP.y;
		}
		else{
			c.x = circumcentre.x;
			c.y = circumcentre.y;
		}

		sleep(10);
		
	}

	CERCLE resultat;
	resultat.x = c.x;
	resultat.y = c.y;
	resultat.d = 2*distance(c,p);
	return resultat;
}
