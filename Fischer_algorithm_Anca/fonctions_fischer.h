#ifndef FONCTIONS_FISCHER_H_
#define FONCTIONS_FISCHER_H_


int estEgal( CERCLE c1, CERCLE c2 );

double distance(POINT a, POINT b);

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