
/* Fichier contenant différentes fonctions de mise à jour de sphères englobantes
 * Les fonctions sont issues d'articles cité dans le papier de Kallberg et Larsson:
	- Yıldırım - Two algorithms for the minimum enclosing problem 
	- Kallberg, Larsson - Fast and robust appx of smallest enclosing balls
	- Badoiu, Clarkson - Smaller core sets for balls
 */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include <math.h>
#include <float.h>


/*
Yıldırım - Two algorithms for the minimum enclosing problem (1 of 2) [16]
*/

POINT_AND_R methodYildirim1 ();

/*
Yıldırım - Two algorithms for the minimum enclosing problem (2 of 2) [16]
*/

POINT_AND_R methodYildirim2 ();

/*
Kallberg, Larsson - Fast and robust appx of smallest enclosing balls [12]
*/

POINT_AND_R methodKallbergLarsson ();


/**
 * Badoiu, Clarkson - Smaller core sets for balls [2]
 *
 * @param center le centre de la sphère courante
 * @param radius le rayon de la sphère courante (pas d'intérêt)
 * @param farthest le point de l'ensemble le plus loin du cnetre
 * @return Y structure contenant le nouveau centre et le nouveau rayon
**/

POINT_AND_R methodBadoiuClarkson ( POINT center , double radius , POINT farthest);