#include <stdio.h>
#include <stdlib.h> 

void calculNorme (POINT* tab, int N);
int argmax(POINT point, POINT* tab, int N);
int argmax2(POINT point, POINT* tab, int N);
double distance(POINT point1, POINT point2);
CERCLE SimpleIterativeBall(POINT*tab, int N, float e);
void display(POINT* tab, int N);
CERCLE ApproximateCoreSet(POINT*tab, int N, float e);
double distanceCoreSet(POINT *tab1,int N1, POINT *tab2, int N2);
