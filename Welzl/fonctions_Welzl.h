#include "structures.h"

void randomisationTableau(POINT *P, int tailleP);
int Pointrand (int tailleP);
CERCLE *b_md(POINT *R,int casesRemplies);
int defined(CERCLE *C,POINT *P,int taille);
CERCLE *B_MINIDISK(POINT *P,POINT *R,int tailleP,int casesRempliesR);
CERCLE *MINIDISK(POINT *P,int tailleP);
