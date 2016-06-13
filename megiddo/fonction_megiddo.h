#ifndef fonction_megiddo_h
#define fonction_megiddo_h
#define SUPERIEUR 1
#define INFERIEUR 0
#define EGAL 2
#define PI 3.14159265
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structure.h"
#include "utils.h"
#include "utils_table.h"




int triAbscisse(POINT tab[],int taille);
DOUBLET* tableauValeurCritique(POINT tab[],int longueur,int ordonne);
DOUBLET* calculAngleCritique(POINT tab[],int longueur);
int calculPositionSolution(POINT tab[],int longueur,double mediane);
int pruningContraint(POINT point[],int longueur,int ordonne);
POINT* intersectionLigne(DOUBLET tab[],int longueur);

#endif