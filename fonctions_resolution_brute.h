#include <stdio.h>
#include <stdlib.h>

#include "structures.h"


CERCLE cerclePassantParDeuxPoints( POINT p1 , POINT p2);

CERCLE cerclePassantParTroisPoints( POINT p1 , POINT p2 , POINT p3);

int contientTousPoint( CERCLE c , POINT tab[], int nbPoints );