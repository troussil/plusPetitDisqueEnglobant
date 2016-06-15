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

	CERCLE vraiC; //Solution universelle pour les 3 tests
	vraiC.x = 10; vraiC.y=10; vraiC.d=10.0;	

	// Test 1 : Points cocirculaires

	POINT tab1[] = {{10,15},{10,5},{5,10},{15,10}};	
	printf("\n** Test 1 : Points cocirculaires **\n\n");
	int nbPoints = sizeof(tab1) / sizeof (tab1[0]);
	printf("Nombre de points: %d\n",nbPoints);
	CERCLE c1 = brute(tab1,nbPoints);
	printf("Cercle solution brute: Coordonnées x=%lf, y=%lf, diamètre=%lf.\n",c1.x,c1.y,c1.d);
	printf("Le résultat devrait être x=10, y=10, d=10\n");

	// Test 2 : Points alignés

	POINT tab2[] = {{10,15},{10,14},{10,5},{10,7}};	
	printf("\n** Test 2 : Points alignés **\n\n");
	nbPoints = sizeof(tab2) / sizeof (tab2[0]);
	printf("Nombre de points: %d\n",nbPoints);
	CERCLE c2 = brute(tab2,nbPoints);
	printf("Cercle solution brute: Coordonnées x=%lf, y=%lf, diamètre=%lf.\n",c2.x,c2.y,c2.d);
	printf("Le résultat devrait être x=10, y=10, d=10\n");

	// Test 3 : Points confondus

	POINT tab3[] = {{10,10},{10,10},{10,10},{10,15},{10,5}};	
	printf("\n** Test 3 : Points confondus **\n\n");
	nbPoints = sizeof(tab3) / sizeof (tab3[0]);
	printf("Nombre de points: %d\n",nbPoints);
	CERCLE c3 = brute(tab3,nbPoints);
	printf("Cercle solution brute: Coordonnées x=%lf, y=%lf, diamètre=%lf.\n",c3.x,c3.y,c3.d);
	printf("Le résultat devrait être x=10, y=10, d=10\n");

	// Test 4 : Points en carré

	POINT tab4[] = {{0,10},{10,10},{0,0},{10,0}};	
	printf("\n** Test 4 : Points en carrés **\n\n");
	nbPoints = sizeof(tab4) / sizeof (tab4[0]);
	printf("Nombre de points: %d\n",nbPoints);
	CERCLE c4 = brute(tab4,nbPoints);
	printf("Cercle solution brute: Coordonnées x=%lf, y=%lf, diamètre=%lf.\n",c4.x,c4.y,c4.d);
	printf("Le résultat devrait être x=5, y=5, d=14.142...\n");

	// Résultat

	if ( estEgal(c1, vraiC) && estEgal(c2, vraiC) && estEgal(c3, vraiC) ){
	   printf(" \n\n     => Résultat CONFORME! \n\n");
	   return 0;  
	} else {
	   printf(" \n\n     => Résultat NON CONFORME! \n\n");
	   return 1; 
	}

}
