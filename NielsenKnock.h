#include <stdio.h>
#include <stdlib.h> 

void calculNorme (POINT* tab, int N);
int argmax(POINT point, POINT* tab, int N);
int argmax2(POINT point, POINT* tab, int N);
double distance(POINT point1, POINT point2);
CERCLE SimpleIterativeBall(POINT*tab, int N, double e);
void display(POINT* tab, int N);
CERCLE ApproximateCoreSet(POINT*tab, int N, double e);
double distanceCoreSet(POINT point, POINT *tab, int N);
