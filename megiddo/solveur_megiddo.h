#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "structure.h"


#define TAILLEPOINT 3 //Diametre d'un point


POINT* convertirEntree (int N);
char* dessinerCercle(FILE *file, int x, int y, int r);
char* dessinerPoint(FILE *file, double x, double y, int r);
void ecritureSVG(POINT tab[], FILE* file , int N);
void GenerationFichierSVG(POINT tab[] , int N);