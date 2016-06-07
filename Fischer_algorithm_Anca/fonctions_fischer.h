#ifndef FONCTIONS_FISCHER_H_
#define FONCTIONS_FISCHER_H_


int estEgal( CERCLE c1, CERCLE c2 );

//calcule la distance entre les points a et b
double distance(POINT a, POINT b);

double calculer_determinant(POINT a, POINT b, POINT c);

//verifie si les coefficients de p dans l'espace engeindre par M sont negatifs (pour le dropping)
int coefficients_negatifs(POINT p,POINT T[], int nbPoints);

//retourne 1 si p appartient a conv(T), 0 sinon
int appartenance_conv(POINT p,POINT T[], int nbPoints);

//retourne 1 si p appartient a aff(T), 0 sinon
int appartenance_aff(POINT p,POINT T[], int nbPoints);

void dropping(POINT T[], int nbPoints);

void walking(POINT* c, POINT T[], int nbPoints);


CERCLE algorithme_fischer(POINT S[], int nbPoints);

#endif