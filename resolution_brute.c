#include <stdio.h>
#include <stdlib.h>

#include "fonctions_resolution_brute.h"


/**
 * @param tab Tableau contenant les points
 * @return cFinal CERCLE solution finale
**/
CERCLE brute( POINT tab[] , int nbPoints ){

	CERCLE cFinal , cTemp;
	cFinal.d = 100000000000; cFinal.x = 0; cFinal.y=0;	

	POINT p1 , p2 , p3;
	
	int i , j , k;

	/* TESTS AVEC DUO DE POINTS */

	printf("Tests avec duo de points...\n");

	for(i=0 ; i<nbPoints ; i++){
		for(j=i+1 ; j<nbPoints ; j++){
			p1 = tab[i];
			p2 = tab[j];
			cTemp = cerclePassantParDeuxPoints(p1 , p2);
			if ( contientTousPoint(cTemp , tab , nbPoints) && cTemp.d < cFinal.d){
				cFinal = cTemp;
			}
		}
	}

	/* TESTS AVEC TRIO DE POINTS */   

	printf("Tests avec trio de points...\n");

	for(i=0 ; i<nbPoints ; i++){
                for(j=0 ; j<nbPoints ; j++){
                        for(k=0 ; k<nbPoints ; k++){
				if(i!=j && i!=k && j!=k){
                                	p1 = tab[i];
                                	p2 = tab[j];
					p3 = tab[k];
                        	        cTemp = cerclePassantParTroisPoints(p1 , p2 , p3);
                              	  	if ( contientTousPoint(cTemp , tab , nbPoints) && cTemp.d < cFinal.d){
                                	        cFinal = cTemp;
                                	}
				}
                        }
                }
        }   

	return cFinal;
}


