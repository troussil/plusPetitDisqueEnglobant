#ifndef FONCTIONS_FISCHER_H_
#define FONCTIONS_FISCHER_H_



/****************************** fonctions print **************************************/

void print_point(POINT* p);

void print_cercle(CERCLE* c);

void print_polygon(polygon *p);

/*************************************************************************************/


/****************************** fonctions geometriques *******************************/
  
double distance(POINT a, POINT b);

double signed_triangle_area(POINT a, POINT b, POINT c);

int collinear(POINT a, POINT b, POINT c);

int tableau_collinear(POINT T[], int nbPoints);


int estEgalCercle( CERCLE c1, CERCLE c2 );

int estEgalPoint( POINT p1, POINT p2 );

int appartenance_conv(POINT p,POINT T[], int nbPoints);

int appartenance_aff(POINT p,POINT T[], int nbPoints);

double calculer_determinant3(POINT a, POINT b, POINT c);

double calculer_determinant2(POINT a, POINT b);

int coefficients_negatifs(POINT p,POINT T[], int nbPoints);

CERCLE cerclePassantParDeuxPoints( POINT p1 , POINT p2);

CERCLE cerclePassantParTroisPoints( POINT p1 , POINT p2 , POINT p3);


/*************************************************************************************/


/**************************** fonctions pour les tableaux ****************************/

void sort_and_remove_duplicates(POINT in[], int *n);

void init_tab(POINT tab[], int nbPoints);

int not_in(POINT tab[], POINT element, int nbPoints);

/**************************** fonctions specifiques a l'algo *************************/

int dropping(POINT c,POINT T[], int nbPoints);

CERCLE algorithme_fischer(POINT S[], int nbPoints);


/**************************** fonctions resolution brute *************************/

//Renvoie 1 si tous les point du tableau tab sont contenus dans le cercle c

int contientTousPoint( CERCLE c , POINT tab[] , int nbPoints );

int contientPoint( CERCLE c , POINT p);

/**
 * @param tab Tableau contenant les points
 * @return cFinal CERCLE solution finale
**/
CERCLE brute( POINT tab[] , int nbPoints );

#endif