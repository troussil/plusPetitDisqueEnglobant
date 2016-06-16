#ifndef FONCTIONS_FISCHER_H_
#define FONCTIONS_FISCHER_H_



/****************************** fonctions print **************************************/

void print_point(POINT* p);

void print_droite(DROITE* d);

void print_cercle(CERCLE* c);

/*************************************************************************************/


/****************************** fonctions geometriques *******************************/

/**
 * Fonction qui calcule la distance entre les points a et b
 * @param a le premier point
 * @param b le deuxieme point
 * @return (double) la distance entre les 2 points
**/
double distance(POINT a, POINT b);

/**
 * Fonction qui calcule l'aire du triangle defini par les points a,b,c
 * @params POINT a,b,c
 * @return (double) l'aire
**/
double signed_triangle_area(POINT a, POINT b, POINT c);

/**
 * Verifie si les points a,b,c sont alignes
 * @params POINT a,b,c
 * @return 1 si points colineaires, 0 sinon
**/
int collinear(POINT a, POINT b, POINT c);


/**
 * Verifie si les d'un tableau
 * @params T tableau points
 * @params nbPoints nombre d'elements dans T
 * @return 1 si points colineaires, 0 sinon
**/
int tableau_collinear(POINT T[], int nbPoints);

/**
 * Verifie si 2 cercles sont egaux
 * @params c1 premier CERCLE
 * @params c2 deuxieme CERCLE
 * @return 1 si cercles egaux, 0 sinon
**/
int estEgalCercle( CERCLE c1, CERCLE c2 );

/**
 * Verifie si 2 points sont egaux
 * @params p1 premier POINT
 * @params p2 deuxieme POINT
 * @return 1 si points egaux, 0 sinon
**/
int estEgalPoint( POINT p1, POINT p2 );


/**
 * Verifie si p appartient a l'enveloppe convexe engeindre par T
 * @params p POINT a verifier
 * @params T tableau points
 * @params nbPoints nombre d'elements dans T
 * @return 1 si p appartient a conv(T), 0 sinon
**/
int appartenance_conv(POINT p,POINT T[], int nbPoints);


/**
 * Verifie si p appartient a l'espace affine engeindre par T
 * @params p POINT a verifier
 * @params T tableau points
 * @params nbPoints nombre d'elements dans T
 * @return 1 si p appartient a aff(T), 0 sinon
**/
int appartenance_aff(POINT p,POINT T[], int nbPoints);

/**
 * calcule le determinant:
 * | a.x  b.x  c.x |
 * | a.y  b.y  c.y |
 * |  1    1    1  |
 *
 * @params POINT a,b,c
 * @return (double) valeur du determinant
**/
double calculer_determinant3(POINT a, POINT b, POINT c);


/**
 * calcule le determinant:
 * | a.x  b.x |
 * | a.y  b.y |
 *
 * @params POINT a,b
 * @return (double) valeur du determinant
**/
double calculer_determinant2(POINT a, POINT b);

/**
 * calcule l'index d'un POINT avec des coeffs negatifs dans l'ecriture p = alpha*T[i] + betha*T[j]
 * @params p POINT a verifier
 * @params T tableau points
 * @params nbPoints nombre d'elements dans T
 * @return (int) l'index du point trouve
 *
 **/
int coefficients_negatifs(POINT p,POINT T[], int nbPoints);


/**
 * Calcule le minimal passant par 2 points
 * @params POINT p1,p2
 * @return CERCLE de centre = (milieu p1,p2), diametre = distance(p1,p2)
**/
CERCLE cerclePassantParDeuxPoints( POINT p1 , POINT p2);

/**
 * Calcule le minimal passant par 3 points
 * @params POINT p1,p2,p3
 * @return CERCLE de centre = (intersection mediatrices), diametre = distance(centre,p1)
**/
CERCLE cerclePassantParTroisPoints( POINT p1 , POINT p2 , POINT p3);

/**
 * Calcule l'equation de la droite mediatrice du segment [p1,p2]
 * @params POINT p1,p2
 * @return DROITE mediatrice
**/
DROITE mediatrice(POINT p1, POINT p2);

/**
 * Calcule l'intersection de 2 droites
 * @params DROITE d1,d2
 * @return POINT d'intersection
**/
POINT intersection(DROITE d1, DROITE d2);

/**
 * Calcule l'equation de la droite passant par 2 points
 * @params POINT p1,p2
 * @return DROITE passant par les 2 points
**/
DROITE droitePassantParPoints(POINT p1, POINT p2);


/*************************************************************************************/


/**************************** fonctions pour les tableaux ****************************/


/**
 * Fait un tri du tableau et enleve les dupliques
 * @params in tableau de points
 * @params nbPoints nombre de points dans in
**/
void sort_and_remove_duplicates(POINT in[], int *n);

/**
 * Initialise un tableau avec des points {0,0} partout
 * @params tab tableau de points
 * @params nbPoints nombre de points dans in
**/
void init_tab(POINT tab[], int nbPoints);

/**
 * Verifie si un point se trouve dans un tableau
 * @params tab tableau de points
 * @params nbPoints nombre de points dans in
 * @params element POINT a verifier
**/
int not_in(POINT tab[], POINT element, int nbPoints);

/**************************** fonctions specifiques a l'algo *************************/

/**
 * Efface l'element d'un tableau qui a des coeffs negatifs dans la decomposition c = coeff[i]*T[i]
 * @params T tableau de points
 * @params nbPoints nombre de points dans T
 * @params c POINT a verifier
**/
int dropping(POINT c,POINT T[], int nbPoints);

/**
 * Met en place l'algorithme de Fischer
 * @params S tableau de points
 * @params nbPoints nombre de points dans S
 * @return CERCLE le cercle minimal contenant toutes les points du S
**/
CERCLE algorithme_fischer(POINT S[], int nbPoints);


/**************************** fonctions resolution brute *************************/

//Renvoie 1 si tous les point du tableau tab sont contenus dans le cercle c

/**
 * Verifie si toutes les points d'un tableau sont contenus dans un cercle
 * @params tab tableau de points
 * @params nbPoints nombre de points dans S
 * @params c CERCLE a verifier
 * @return 1 si toutes les points sont contenus dans le cercle, 0 sinon
**/
int contientTousPoint( CERCLE c , POINT tab[] , int nbPoints );

/**
 * Verifie si un point est contenu dans un cercle
 * @params p POINT a verifier
 * @params c CERCLE a verifier
 * @return 1 si toutes le point est contenu dans le cercle, 0 sinon
**/
int contientPoint( CERCLE c , POINT p);

/**
 * @param tab Tableau contenant les points
 * @return cFinal CERCLE solution finale
**/
CERCLE brute( POINT tab[] , int nbPoints );

#endif