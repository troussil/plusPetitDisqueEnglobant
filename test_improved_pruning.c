#include "improved_pruning.h"


int main(){

	printf("\n** Testing improved_pruning.c methods **\n");


	// (1/3) Method farthestPoint

	POINT trueFarthest; //Solution réelle
	trueFarthest.x = 260; trueFarthest.y=280; 	

	POINT tab1[] = {{5,15},{16,5},{5,5},{260,280}};	
	POINT c; c.x = 0; c.y = 0;


	POINT test = farthestPoint( tab1 , 4 , c );

	if (test.x == trueFarthest.x && test.y == trueFarthest.y ){
		printf("Method (1/3) farthestPoint: SUCCESS !\n");
	} else {
		printf("Method (1/3) farthestPoint: FAILURE !\n");
		printf("%d != %d OR/AND %d != %d\n", test.x,trueFarthest.x,test.y,trueFarthest.y);
	}



	// (2/3) Method prune

	POINT tab2[] = {{5,15},{-160,5},{5,5},{260,280}};	
	POINT truePruned[] = {{-160,5},{260,280}}; // La solution pour un critère de 50

	POINTS_AND_NB pruned = prune( tab2 , 4 , c , 50 );  //50 est le critère

	if( pruned.nbPoints==2 && 
		pruned.tab[0].x==truePruned[0].x && 
		pruned.tab[1].x==truePruned[1].x && 
		pruned.tab[0].y==truePruned[0].y && 
		pruned.tab[1].y==truePruned[1].y){
			printf("Method (2/3) prune: SUCCESS !\n\n");
	}else {
			printf("Method (2/3) prune: FAILURE !\n\n");
	}


	// (3/3) Method farthPtPrune




	return 0;
}

