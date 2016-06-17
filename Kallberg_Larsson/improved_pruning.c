
#include "structures.h"
#include "improved_pruning.h"
#include "updateball_methods.h"

/**
 * Algorithme utilisant les théorèmes 2 et 4
 * @param P tableau des points du plan
 * @param nbPoints nombre de points
 * @param apx facteur d'approximation recherché
 * @return sol cercle solution
**/

CERCLE ApxMEB1 ( POINT P[], int nbPoints, double apx){

	int nbPts = nbPoints;
	POINTS_AND_NB X;
	
	int maj = 0;

	CERCLE sol; //Cercle solution

	POINT c;	//Centre du cercle solution
	int r;		//Rayon du cercle solution

	POINT q;	//Point extrême
	int R;		//Distance

	double delta; //distance entre centre du cercle min et centre cercle en cours
	double crit;  //critère de pruning (distance)


	POINT_AND_R Y = initializeBall(P , nbPoints); 
	c = Y.center;
	r = Y.radius; 

	
	q = farthestPoint( P , nbPts , c );
	R = sqrt( ( (c.x - q.x)*(c.x - q.x) ) + ( (c.y - q.y)*(c.y - q.y) ) );

	while( R > r*(1+apx) ){

		delta = sqrt( ((R*R) - (r*r))/2 );
		crit = sqrt((r*r)+(delta*delta)) - delta;
		
		X = prune( P, nbPts, c, crit);
	
		P = X.tab;
		nbPts = X.nbPoints;


		/***** UPDATEBALL ****
		Différentes possibilités avec 2 algos de Yildirim et 1 de Larsson & Källberg et 1 de Badoiu et Clarkson */


		switch(MODE){
			case 1: 
				Y = methodBadoiuClarkson( c , r , q );
				break;
			case 2: 
				Y = methodKallbergLarsson( c , r , q , apx/2);
				break;
			default: exit(-1);
		}

		c = Y.center;
		r = Y.radius;

		maj++;

		/*********************/

		q = farthestPoint( P , nbPts , c );
		R = sqrt( ( (c.x - q.x)*(c.x - q.x) ) + ( (c.y - q.y)*(c.y - q.y) ) );

	}

	if(maj>0){
		free(P);
	}

	printf("\nMises à jour apx1: %d\n",maj);

	sol.x = c.x;
	sol.y = c.y;
	sol.d = 2*R;
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

	int nbPts = nbPoints;
	POINTS_AND_SPD Z;

	int maj = 0;
	
	CERCLE sol; //Cercle solution

	POINT c;	//Centre du cercle solution
	double r;		//Rayon du cercle solution

	POINT q;	//Point extrême
	double R;		//Distance

	POINT cc;	//Centre temporaire
	double RR;		//Distance temporaire

	double delta; //distance entre centre du cercle min et centre cercle en cours
	double gap;	  //distance entre c et cc (delta minuscule dans l'article)
	double crit;  //critère de pruning (distance)

	POINT_AND_R Y = initializeBall(P , nbPoints); 
	c = Y.center;
	r = Y.radius; 

	q = farthestPoint( P , nbPts , c );
	R = sqrt( ( (c.x - q.x)*(c.x - q.x) ) + ( (c.y - q.y)*(c.y - q.y) ) );

	while( R > r*(1+apx) ){

		cc = c;
		RR = R;

		/***** UPDATEBALL ****
		Différentes possibilités avec 2 algos de Yildirim et 1 de Larsson & Källberg et 1 de Badoiu et Clarkson */

		Y = methodBadoiuClarkson( c , r , q );
		c = Y.center;
		r = Y.radius;

		maj++;
		

		/*********************/

		gap = sqrt( ( (c.x - cc.x)*(c.x - cc.x) ) + ( (c.y - cc.y)*(c.y - cc.y) ) );
		delta = ( gap + sqrt(2*(RR*RR - r*r) - gap*gap) )/2;
		crit = sqrt(r*r + delta*delta) - delta;

		Z = farthPtPrune( P , nbPts , c , crit);
		
		P = Z.tab;
		nbPts = Z.nbPoints;
		R = Z.distance;
		q = Z.farthest; 


	}	

	if(maj>0){
		free(P);
	}
	

	printf("\nMises à jour apx2: %d\n",maj);

	sol.x = c.x;
	sol.y = c.y;
	sol.d = 2*R;
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
	double distTemp;
	
	int i;
	for (i = 0; i < nbPoints; i++)
	{
		distTemp = sqrt( ( (c.x - P[i].x)*(c.x - P[i].x) ) + ( (c.y - P[i].y)*(c.y - P[i].y) ) ); //formule de la distance entre 2 points ds le plan
		if (  distTemp > dist){ 
			fp.x = P[i].x;
			fp.y = P[i].y;
			dist = distTemp;
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

	static int callCounter = 0;

	POINTS_AND_NB X; // Structure à retourner
	
	int nbPointsOk = 0; //nbre de points ne vérifiant pas le critère de pruning
 	int i;

	/* Nouveau tableau qui contiendra uniquement les points non "prunés" */
 	POINT* Q = (POINT*) malloc(nbPoints * sizeof(POINT));

 	//printf("\nPointeur mallocé: %p\n",Q );

	/* Ajouter au nouveau tableau tous les points ne vérifiant pas le critère de pruning */
	for (i = 0; i < nbPoints; i++){
		if ( (( (c.x - P[i].x)*(c.x - P[i].x) ) + ( (c.y - P[i].y)*(c.y - P[i].y) )) > dist*dist ){
			Q[nbPointsOk] = P[i]; 
			nbPointsOk++;
		}
	}


	if(callCounter>0){
		//printf("Pointeur précédent à libérer: %p\n",P );
		free(P);
	} else {
		//printf("Aucun pointeur à libérer\n",P );
	}

	callCounter++;


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
 * @return X le tableau de points dont on a ôté des points + le point le plus loin + sa distance au centre
**/

POINTS_AND_SPD farthPtPrune (POINT P[] , int nbPoints , POINT c , double dist){

	static int callCounter = 0;

	POINTS_AND_SPD X; //structure à retourner

	POINT* Q = (POINT*) malloc(nbPoints * sizeof(POINT)); //Nouveau tableau qui contiendra uniquement les points non "prunés"

	//printf("\nPointeur mallocé: %p\n",Q);

	POINT q = {0,0};
	double x = -DBL_MAX;	// =-79769e+308  != -infini (limite de l'algorithme)
	
	int nbPointsOk = 0; //nbre de points ne vérifiant pas le critère de pruning

	//int toPrune[nbPoints] = {0}; //contiendra les index des points à pruner METHODE NON CONSERVEE

	int i;
	double e;

	for (i = 0; i < nbPoints; i++){

		e = (( (c.x - P[i].x)*(c.x - P[i].x) ) + ( (c.y - P[i].y)*(c.y - P[i].y) )); //distance entre c et P[i] au carré

		if ( e < dist*dist ){
			/* Prunage du point P[i] */
			/* = ne pas le sauvegarder */

		} else{ 
			
			/* Sauvegarde du point non pruné */
			Q[nbPointsOk] = P[i]; 
			nbPointsOk++;

			if (e > x)
			{
				q = P[i];
				x = e;
			}
		}
	}

	if(callCounter>0){
		//printf("Pointeur précédent à libérer: %p\n",P );
		free(P);
	} else {
		//printf("Aucun pointeur à libérer\n",P );
	}
	callCounter++;

	X.tab = Q;
	X.nbPoints = nbPointsOk;
	X.farthest = q;
	X.distance = sqrt(x);

	return X;

}

/**
 * Initalise une boule à partir de deux points les plus loin d'un point au hasard parmi un ensemble.
 * @param P ensemble de points
 * @param nbPoints nombre de points
 * @return X le centre initialisé + le rayon
**/

POINT_AND_R initializeBall (POINT P[] , int nbPoints){

	POINT_AND_R X;
	POINT temp;

	int randIndex = rand()%(nbPoints+1);
	temp.x = P[randIndex].x;
	temp.y = P[randIndex].y;

	POINT q1 = farthestPoint( P , nbPoints, temp);
	POINT q2 = farthestPoint( P , nbPoints, q1);

	X.center.x = (q2.x + q1.x)/2;
	X.center.y = (q2.y + q1.y)/2;

	X.radius = sqrt( ( (q1.x - q2.x)*(q1.x - q2.x) ) + ( (q1.y - q2.y)*(q1.y - q2.y) ) ) /2;

	return X;

}