#include <stdio.h>
#include <stdlib.h>

#include "resolution_brute.h"

int main(){

	POINT tab[5] = {{10,10},{10,15},{10,5},{5,10},{15,10}};	
	int nbPoints = sizeof(tab) / sizeof (tab[0]);
	
	printf("Nombre de points: %d\n",nbPoints);

	CERCLE c = brute(tab,nbPoints);

	
	
	printf("Cercle solution brute: Coordonnées x=%d, y=%d, diamètre=%lf.\n",c.x,c.y,c.d);
	printf("Le résultat devrait être x=10, y=10, d=10\n");

	/* if ( estEgal(c, vraiC) ) */
	/*   return 0;  */
	/* else  */
	/*   return 1; */

	return 0;
}
