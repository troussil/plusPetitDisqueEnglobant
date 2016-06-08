#ifndef FONCTIONS_FISCHER_H_
#define FONCTIONS_FISCHER_H_

#include "structures.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double min(double a, double b);

double max(double a, double b);

double distance(POINT a, POINT b);

/***********************************************************************/

void copy_point(POINT a, POINT b);

void swap_point(POINT a, POINT b);


double signed_triangle_area(POINT a, POINT b, POINT c);

double triangle_area(POINT a, POINT b, POINT c);

bool ccw(POINT a, POINT b, POINT c);

bool cw(POINT a, POINT b, POINT c);

bool collinear(POINT a, POINT b, POINT c);

void print_points(POINT p[], int n);

void print_point(POINT* p);

void print_polygon(polygon *p);




void sort_and_remove_duplicates(POINT in[], int *n);



bool leftlower(POINT *p1, POINT *p2);

bool smaller_angle(POINT *p1, POINT *p2);



void convex_hull(POINT in[], int n, polygon *hull);


int estEgal( CERCLE c1, CERCLE c2 );

int pointsColineaires(POINT T[], int nbPoints);

double calculer_determinant3(POINT a, POINT b, POINT c);

double calculer_determinant2(POINT a, POINT b);

int coefficients_negatifs(POINT p,POINT T[], int nbPoints);

int appartenance_conv(POINT p,POINT T[], int nbPoints);

int appartenance_aff(POINT p,POINT T[], int nbPoints);

void dropping(POINT T[], int nbPoints);

void walking(POINT* c, POINT T[], int nbPoints);


CERCLE algorithme_fischer(POINT S[], int nbPoints);

#endif