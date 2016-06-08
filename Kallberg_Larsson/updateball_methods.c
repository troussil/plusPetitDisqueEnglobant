
#include "structures.h"
#include "updateball_methods.h"


/**
 * Badoiu, Clarkson - Smaller core sets for balls [2]
 * @param center le centre de la sphère courante
 * @param radius le rayon de la sphère courante
 * @param farthest le point de l'ensemble le plus loin du cnetre
 * @return Y structure contenant le nouveau centre et le nouveau rayon (l'ancien en fait.. faudra recalculer avec farthestPoint)
**/

POINT_AND_R methodBadoiuClarkson ( POINT center , double radius , POINT farthest){

	static double step = 1.0;	//s'incrémentera à chaque appel

	POINT_AND_R Y;
	POINT c;

	c.x = center.x + (farthest.x - center.x) * ( 1/ (step+1) ) ;
	c.y = center.y + (farthest.y - center.y) * ( 1/ (step+1) ) ;

	
	step = step+1;

	Y.center = c;

	Y.radius = sqrt( ( (c.x - farthest.x)*(c.x - farthest.x) ) + ( (c.y - farthest.y)*(c.y - farthest.y) ) );	
	//Petit doute... pas décrit dans l'article. Le "farthest" n'est plus le point le plus loin à ce moment là !
	//Utilisation de l'argument radius ? -> ici farthest.x - center.x
	
	return Y;

}