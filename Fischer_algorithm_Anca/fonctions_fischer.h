#ifndef FONCTIONS_FISCHER_H_
#define FONCTIONS_FISCHER_H_

#include "structures.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


double distance(POINT a, POINT b);

double signed_triangle_area(POINT a, POINT b, POINT c);

int ccw(POINT a, POINT b, POINT c);

int cw(POINT a, POINT b, POINT c);

int collinear(POINT a, POINT b, POINT c);

void sort_and_remove_duplicates(POINT in[], int *n);

int leftlower(POINT *p1, POINT *p2);

int smaller_angle(POINT *p1, POINT *p2);

void convex_hull(POINT in[], int n, polygon *hull);

int estEgal( CERCLE c1, CERCLE c2 );

int tableau_collinear(POINT T[], int nbPoints);

double calculer_determinant3(POINT a, POINT b, POINT c);

double calculer_determinant2(POINT a, POINT b);

int coefficients_negatifs(POINT p,POINT T[], int nbPoints);

int appartenance_conv(POINT p,POINT T[], int nbPoints);

int appartenance_aff(POINT p,POINT T[], int nbPoints);

void dropping(POINT T[], int nbPoints);

void walking(POINT* c, POINT T[], int nbPoints);

CERCLE algorithme_fischer(POINT S[], int nbPoints);

#endif