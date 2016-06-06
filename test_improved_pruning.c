#include "improved_pruning.h"


int main(){

	printf("\n** Testing improved_pruning.c methods **\n");


	// (1/3) Method farthestPoint

	POINT trueFarthest; //Solution réelle
	trueFarthest.x = 260; trueFarthest.y=280; 	

	POINT tab1[] = {{5,15},{16,5},{5,5},{260,280}};	
	POINT c; c.x = 0; c.y = 0;


	POINT test = farthestPoint( tab1 , 4 , c );
	printf("Method (1/3) farthestPoint: ");

	if (test.x == trueFarthest.x && test.y == trueFarthest.y ){
		printf("SUCCESS !\n");
	} else {
		printf("FAILURE !\n");
		printf("%d != %d OR/AND %d != %d\n", test.x,trueFarthest.x,test.y,trueFarthest.y);
	}


	// (2/3) Method prune

	POINT tab2[] = {{5,15},{-160,5},{5,5},{260,280}};	
	POINT truePruned[] = {{-160,5},{260,280}}; // La solution pour un critère de 50

	POINTS_AND_NB pruned = prune( tab2 , 4 , c , 50 );  //50 est le critère
	printf("Method (2/3) prune: ");

	if( pruned.nbPoints==2 && 
		pruned.tab[0].x==truePruned[0].x && 
		pruned.tab[1].x==truePruned[1].x && 
		pruned.tab[0].y==truePruned[0].y && 
		pruned.tab[1].y==truePruned[1].y){
			printf("SUCCESS !\n");
	}else {
			printf("FAILURE !\n");
	}


	// (3/3) Method farthPtPrune

	POINTS_AND_SPD farthpruned = farthPtPrune(tab2 , 4 , c , 50);
	printf("Method (3/3) farthPtPrune: ");

	double trueDist = sqrt(((c.x - truePruned[1].x)*(c.x - truePruned[1].x))+((c.y - truePruned[1].y)*(c.y - truePruned[1].y)));

	if( farthpruned.farthest.x == trueFarthest.x &&
		farthpruned.farthest.y == trueFarthest.y &&
		farthpruned.distance == trueDist &&
		farthpruned.nbPoints==2 && 
		farthpruned.tab[0].x==truePruned[0].x && 
		farthpruned.tab[1].x==truePruned[1].x && 
		farthpruned.tab[0].y==truePruned[0].y && 
		farthpruned.tab[1].y==truePruned[1].y){
			printf("SUCCESS !\n\n");			
	}else {
			printf("FAILURE !\n\n");
	}


	return 0;
}

