#include <stdio.h>
#include <stdlib.h>

#include "resolution_brute.h"


/**
 * Teste si deux cercles c1 et c2 sont égaux
**/
int estEgal( CERCLE c1, CERCLE c2 ){
	if( (c1.x == c2.x) && (c1.y == c2.y) && (c1.d == c2.d) )
		return 1;
	else
		return 0;
} 
	

int main(){

	POINT tab[5] = {{10,10},{10,15},{10,5},{5,10},{15,10}};	
	CERCLE vraiC; //Solution
	vraiC.x = 10; vraiC.y=10; vraiC.d=10.0;	

	int nbPoints = sizeof(tab) / sizeof (tab[0]);
	
	printf("Nombre de points: %d\n",nbPoints);

	CERCLE c = brute(tab,nbPoints);

	
	
	printf("Cercle solution brute: Coordonnées x=%d, y=%d, diamètre=%lf.\n",c.x,c.y,c.d);
	printf("Le résultat devrait être x=10, y=10, d=10\n");

	if ( estEgal(c, vraiC) ){
	   printf("Résultat conforme! \n");
	   return 0;  
	} else {
	   printf("Résultat NON CONFORME! \n");
	   return 1; 
	}
}
