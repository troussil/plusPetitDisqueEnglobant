#ifndef solution_brute_contrainte_h
#define solution_brute_contrainte_h
#include "structure.h"
#include "utils.h"
#include "utils_table.h"


CERCLE* solutionBruteContrainte(POINT tab[],int Nbpoint,double yc);
CERCLE* ensembleUnPoint(POINT tab[],int Nbpoint,double yc);
CERCLE* ensembleDeuxPoints(POINT tab[], int Nbpoint, double yc);
int estContenuCercle(CERCLE c,POINT a);
TABPOINT* compteurCercle(CERCLE c,POINT tab[],int longueur);



#endif