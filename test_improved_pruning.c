#include "improved_pruning.h"


int main(){

	printf("\n** Testing improved_pruning.c methods **\n");


	// (1/3) Method farthestPoint

	POINT trueFarthest; //Solution réelle
	trueFarthest.x = 260; trueFarthest.y=280; 	

	POINT tab[] = {{5,15},{16,5},{5,5},{260,280}};	
	POINT c; c.x = 0; c.y = 0;


	POINT test = farthestPoint (tab,4,c);

	if (test.x == trueFarthest.x && test.y == trueFarthest.y ){
		printf("Method (1/3) farthestPoint: SUCCESS !\n\n");
	} else {
		printf("Method (1/3) farthestPoint: FAILURE !\n");
		printf("%d != %d OR/AND %d != %d\n", test.x,trueFarthest.x,test.y,trueFarthest.y);
	}



	// (2/3) Method prune






	// (3/3) Method farthPtPrune




	return 0;
}

