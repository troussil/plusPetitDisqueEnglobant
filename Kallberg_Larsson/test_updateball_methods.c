#include "updateball_methods.h"
#include "improved_pruning.h"

int main(){

	printf("\n** Testing updateball_methods.c methods **\n\n");

	// (1/4) Méthode methodBadoiuClarkson

	POINT tab1[] = {{0,100},{0,-100},{0,40},{0,-10},{0,80},{0,-90},{0,-100},{0,40},{0,-10},{0,80},{0,-90},{0,60},{0,-30},{0,-100},{0,40},{0,-10},{0,80},{0,-90},{0,60},{0,-30}};	
	int nbPoints = 20;

	printf("Method (1/4) methodBadoiuClarkson: \n");

	POINT c = tab1[4];	//Au hasard
	printf("_Centre initial: (%lf , %lf)\n", c.x, c.y);
	int i;
	POINT_AND_R X;
	POINT farthest;

	double apx = 0.001;
	printf("_Apx du centre à %lf près\n...\n", apx );

	for (i = 0; i < 1 + (int) 1/(apx*apx) ; i++)
	{
		farthest = farthestPoint( tab1 , nbPoints , c);
		X = methodBadoiuClarkson( c , 0 /*car on l'utilise pas dans la méthode */ , farthest );
		c = X.center;	
	}

	printf("_Centre final: (%lf , %lf)\n->", c.x, c.y );
	
	if( fabs(c.x)<=apx && fabs(c.y)<=apx ) {
			printf("SUCCESS !\n\n");
	}else {
			printf("FAILURE !\n\n");
	}



	// (2/4) Méthode methodYildirim1

	// (3/4) Méthode methodYildirim2
	
	// (4/4) Méthode methodKallbergLarsson



	return 0;

	}