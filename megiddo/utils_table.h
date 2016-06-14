#ifndef utils_table_h
#define utils_table_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structure.h"

void afficherTableauPoint(POINT tab[],int taille);
void afficherTableauDoublet(DOUBLET tab[],int taille);
void afficherTableauDroite(DOUBLET tab[],int taille);
void echangerDoublet(DOUBLET tableau[], int a, int b);
void echangerPoint(POINT tableau[], int a, int b);
void quickSortDoubletMediatrice(DOUBLET tableau[], int debut, int fin);
void quickSortDoubletAngle(DOUBLET tableau[], int debut, int fin);
void quickSortPoint(POINT tableau[], int debut, int fin);
double medianeMediatrice(DOUBLET tableau[],int longueur);
double medianeAngle(DOUBLET tableau[],int longueur);
double triAngle(DOUBLET tableau[], int debut, int fin);
double triMediatrice(DOUBLET tableau[], int debut, int fin);



#endif