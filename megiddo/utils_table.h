#ifndef utils_table_h
#define utils_table_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structure.h"

void afficherTableauPoint(POINT tab[],int taille);
void afficherTableauDouble(double tab[],int taille);
void echanger(double tableau[], int a, int b);
void quickSort(double tableau[], int debut, int fin);
double mediane(double tableau[],int longueur);



#endif