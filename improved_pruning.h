#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include <math.h>
#include <float.h>


/**
 * Une structure permettant de retourner un tableau de points et la taille qu'il fait
 * (utilisé pour la méthode prune)
**/ 

typedef struct tabOfPoints_and_size{
    POINT* tab;
	int nbPoints;
} POINTS_AND_NB;

/**
 * Une structure permettant de retourner un tableau de points, la taille qu'il fait, le point le plus loin, et une distance
 * (utilisé pour la méthode farthPtPrune)
**/ 

typedef struct tabOfPoints_and_size_and_point_and_dist{
    POINT* tab;
	int nbPoints;
	POINT farthest;
	double distance;
} POINTS_AND_SPD;


/**
 * Une structure permettant de retourner un centre et un rayon
 * (utilisé pour la méthode initializeBall et updateBall)
**/ 

typedef struct point_and_dist{
    POINT center;
	double radius;
} POINT_AND_R;


/**
 * Algorithme utilisant les théorèmes 2 et 4
 * @param P tableau des points du plan
 * @param nbPoints nombre de points
 * @param apx facteur d'approximation recherché
 * @return sol cercle solution
**/

CERCLE ApxMEB1 ( POINT P[], int nbPoints, double apx);


/**
 * Algorithme utilisant les théorèmes 3 et 4
 * @param P tableau des points du plan
 * @param nbPoints nombre de points
 * @param apx facteur d'approximation recherché
 * @return sol cercle solution
**/

CERCLE ApxMEB2 ( POINT P[], int nbPoints, double apx);


/**
 * Cherche le point le plus loin d'un autre point
 * @param P tableau des points du plan parmi lesquels chercher
 * @param nbPoints nombre de points
 * @param c point pour lequel on cherche le plus éloigné
 * @return f le point le plus loin
**/

POINT farthestPoint (POINT P[] , int nbPoints , POINT c);


/**
 * Ôte un ou plusieurs points de l'ensemble de points
 * @param P ensemble de points
 * @param c point à considérer comme le centre
 * @param nbPoints nombre de points
 * @param dist critère de distance à considérer pour ôter les points
 * @return Q le tableau de points dont on a ôté des points
**/

POINTS_AND_NB prune (POINT P[] , int nbPoints , POINT c , double dist);

/**
 * On regarde si chaque point de l'ensemble remplit la condition de pruning, et si ce n'est pas le cas on regarde s'il est le plus loin.
 * @param P ensemble de points
 * @param c point à considérer comme le centre
 * @param dist critère de distance à considérer pour ôter les points
 * @return X le tableau de points dont on a ôté des points + le point le plus loin + sa distance au centre
**/

POINTS_AND_SPD farthPtPrune (POINT P[] , int nbPoints , POINT c , double dist);

/**
 * Initalise une boule à partir de deux points les plus loin parmi un ensemble.
 * @param P ensemble de points
 * @param nbPoints nombre de points
 * @return X le centre initialisé + le rayon
**/

POINT_AND_R initializeBall (POINT P[] , int nbPoints);