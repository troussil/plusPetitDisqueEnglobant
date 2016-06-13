#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structure.h"

double auCarre(double v);
double distance(POINT a , POINT b);
POINT* distanceInf(POINT xm, POINT *a, POINT *b);
int partiEntiere(int a);
void calculDroite(DOUBLET tab[],int longueur);
int estParallele(DOUBLET d1, DOUBLET d2);
POINT* calculIntersection(DOUBLET d1, DOUBLET d2);