#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "structure.h"


#define TAILLEPOINT 3 //Diametre d'un point


POINT* convertirEntree (int N);
char* dessinerCercleAmeliore(FILE *file,CERCLE c);
char* dessinerCercleBrute(FILE *file,CERCLE c);
char* dessinerPoint(FILE *file, double x, double y, int r);
void ecritureSVG(POINT tab[], FILE* file , int N,int yc,int x1,int x2);
void GenerationFichierSVG(POINT tab[] , int N, int yc,int x1,int x2);
char* dessinerPointElagage(FILE *file, double x, double y, int r);
char* dessinerLigneContrainte(FILE *file,int yc,int x1,int x2);
