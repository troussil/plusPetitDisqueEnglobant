#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structures.h"

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
 * calcule la distance entre les points a et b
**/
double distance(POINT a, POINT b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
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

//retourne l'index d'un point avec des coeffs negatifs dans l'ecriture p = alpha*T[i] + betha*T[j]
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
	//si les point de T sont allignes, il faut que p appartienne a la droite pour qu'il appartienne a aff(T)
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

	printf("in function c.x = %d c.y = %d\n", c.x, c.y); 

	POINT p; // le point le plus eloigne de c
	double max=0;
	for(int i=1; i<nbPoints;i++)
    {
    	POINT q = S[i];
    	printf("in function q.x = %d q.y = %d\n", q.x, q.y);
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
