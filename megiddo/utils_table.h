#ifndef utils_table_h
#define utils_table_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structure.h"

void afficherTableauPoint(POINT tab[],int taille);
void afficherTableauDoublet(DOUBLET tab[],int taille);
void echanger(DOUBLET tableau[], int a, int b);
void quickSort(DOUBLET tableau[], int debut, int fin);
double mediane(DOUBLET tableau[],int longueur);

#endif