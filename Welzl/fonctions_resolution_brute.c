#include "structures.h"
#include <math.h>
#include "fonctions_resolution_brute.h"

//Renvoie le cercle le plus petit passant par deux points p1 et p2
 
CERCLE *cerclePassantParDeuxPoints( POINT p1 , POINT p2){
	
	CERCLE *c;
  c = malloc (sizeof(CERCLE));		
	c->x = (p1.x + p2.x)/2;
	c->y = (p1.y + p2.y)/2;
	c->d = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	
	//printf("cercle renvoye : x = %d, y = %d, d = %f\n", c.x, c.y, c.d);
	return c;	
}


//Renvoie le cercle le plus petit passant par trois points p1, p2, et p3

CERCLE *cerclePassantParTroisPoints( POINT p1 , POINT p2 , POINT p3){
	
	CERCLE *c;
  c = malloc (sizeof(CERCLE));	
	float det =  (p1.x - p2.x) * (p2.y - p3.y) - (p2.x - p3.x)* (p1.y - p2.y); 

  if (det == 0) { 
		c->d = 100000000000; 
		c->x = 0; 
		c->y=0; 
	} else {
		int offset = pow(p2.x,2) + pow(p2.y,2);
    		int bc =   ( pow(p1.x,2) + pow(p1.y,2) - offset )/2.0;
    		int cd =   (offset - pow(p3.x, 2) - pow(p3.y, 2))/2.0;

	    	c->x =  (bc * (p2.y - p3.y) - cd * (p1.y - p2.y)) / det;
	    	c->y =  (cd * (p1.x - p2.x) - bc * (p2.x - p3.x)) / det;
	    	c->d = 2 * sqrt( pow(p2.x - c->x,2) + pow(p2.y-c->y,2));
	}
	//printf("cercle renvoye : x = %d, y = %d, d = %f\n", c.x, c.y, c.d);
	return c;	
}


//Renvoie 1 si tous les point du tableau tab sont contenus dans le cercle c

int contientTousPoint( CERCLE *c , POINT tab[] , int nbPoints ){
	
	int i = 0;	
	int ok = 1;
	
	while(i<nbPoints && ok) {
	  if (!contientPoint( c, tab[i] ))
	    ok = 0;
	  i++;
	}
	
	return ok;
}

int contientPoint( CERCLE *c , POINT p){

	if(c->x + c->d/2 < p.x || c->x - c->d/2 > p.x || c->y + c->d/2 < p.y || c->y - c->d/2 > p.y)
		return 0;
	else
		return 1;

}
