
#include "fonction_megiddo.h"
#include "structure.h"
#include "utils_table.h"

int main(){

	POINT tab[NB_POINTS] = {{2,3},{2,4},{3,5},{4,6},{2,7},{3,8},{1,2},{5,4},{2,8},{3,9}};	
	//afficherTableau(tab);
	POINT *resultat=malloc(NB_POINTS*sizeof(POINT));
	// resultat[nbPoints];
	resultat=triAbscisse(tab,NB_POINTS);
	afficherTableauPoint(resultat,NB_POINTS);
	double *critique=malloc((NB_POINTS/2)*sizeof(double));
	printf("---------------\n");
	critique=tableauValeurCritique(resultat,NB_POINTS);
	afficherTableauDouble(critique,NB_POINTS/2);
	quickSort(critique,0,4);
	printf("trie du tableau: \n");
	afficherTableauDouble(critique,NB_POINTS/2);

}



