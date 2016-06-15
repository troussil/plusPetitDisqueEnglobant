
#include "structures.h"
#include "improved_pruning.h"


/**
 * Algorithme utilisant les théorèmes 2 et 4
 * @param P tableau des points du plan
 * @param nbPoints nombre de points
 * @param apx facteur d'approximation recherché
 * @return sol cercle solution
**/

CERCLE ApxMEB1 ( POINT P[], int nbPoints, double apx){

	POINT c;	//Centre du cercle solution
	int r;		//Rayon du cercle solution
	CERCLE sol; //Cercle solution


	//TO CODE


	return sol;


}



/**
 * Algorithme utilisant les théorèmes 3 et 4
 * @param P tableau des points du plan
 * @param nbPoints nombre de points
 * @param apx facteur d'approximation recherché
 * @return sol le cercle solution
**/

CERCLE ApxMEB2 ( POINT P[], int nbPoints, double apx){

	POINT c;	//Centre du cercle solution
	int r;		//Rayon du cercle solution
	CERCLE sol; //Cercle solution


	//TO CODE


	return sol;


}



/**
 * Cherche le point le plus loin d'un autre point
 * @param P tableau des points du plan parmi lesquels chercher
 * @param nbPoints nombre de points
 * @param c point pour lequel on cherche le plus éloigné
 * @return fp le point le plus loin
**/

POINT farthestPoint (POINT P[] , int nbPoints , POINT c){

	POINT fp;
	double dist = 0.0;
	
	int i;
	for (i = 0; i < nbPoints; i++)
	{
		if ( sqrt( ( (c.x - P[i].x)*(c.x - P[i].x) ) + ( (c.y - P[i].y)*(c.y - P[i].y) ) ) > dist){ //formule de la distance entre 2 points ds le plan
			fp.x = P[i].x;
			fp.y = P[i].y;
		}
	}

	return fp;
	
}


/**
 * Ôte un ou plusieurs points de l'ensemble de points
 * @param P ensemble de points
 * @param c point à considérer comme le centre
 * @param nbPoints nombre de points
 * @param dist critère de pruning: la distance entre le point et le centre c est inférieure à dist
 * @return X contenant le tableau de points dont on a ôté des points + le nombre de points retenus
**/

POINTS_AND_NB prune (POINT P[] , int nbPoints , POINT c , double dist){

	POINTS_AND_NB X; // Structure à retourner
	
	int nbPointsOk = 0; //nbre de points ne vérifiant pas le critère de pruning
 	int i;

	/* Nouveau tableau qui contiendra uniquement les points non "prunés" */
 	POINT* Q = (POINT*) malloc(nbPoints * sizeof(POINT));

	/* Ajouter au nouveau tableau tous les points ne vérifiant pas le critère de pruning */
	for (i = 0; i < nbPoints; i++){
		if ( (( (c.x - P[i].x)*(c.x - P[i].x) ) + ( (c.y - P[i].y)*(c.y - P[i].y) )) > dist*dist ){
			Q[nbPointsOk] = P[i]; 
			nbPointsOk++;
		}
	}

	/* On remplit la structure POINTS_AND_NB avec le tableau pruné et le nombre de points restant */
	X.tab = Q;
	X.nbPoints = nbPointsOk;
	return X;
}


/**
 * On regarde si chaque point de l'ensemble remplit la condition de pruning, et si ce n'est pas le cas on regarde s'il est le plus loin.
 * @param P ensemble de points
 * @param c point à considérer comme le centre
 * @param dist critère de distance à considérer pour ôter les points
 * @return Q le tableau de points dont on a ôté des points + le point (q, sqrt(x))
**/

POINT* farthPtPrune (POINT P[] , POINT c , double dist){


	POINT* Q;

	//TO CODE

	return Q;

}