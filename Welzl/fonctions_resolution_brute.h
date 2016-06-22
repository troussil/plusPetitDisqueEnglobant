#ifndef fonctions_resolution_brute_h
#define fonctions_resolution_brute_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structures.h"


CERCLE *cerclePassantParDeuxPoints( POINT p1 , POINT p2);

CERCLE *cerclePassantParTroisPoints( POINT p1 , POINT p2 , POINT p3);

int contientTousPoint( CERCLE *c , POINT tab[], int nbPoints );

int contientPoint( CERCLE *c , POINT p);

//double distance(POINT a,POINT b);

#endif
