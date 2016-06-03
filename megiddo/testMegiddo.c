
#include "fonction_megiddo.h"
#include "structure.h"
#include "utils_table.h"

int main(){

	POINT tab[NB_POINTS] = {{1,0},{3,2},{3,-2},{4,-5},{5,3},{7,-1},{7,2},{5,5},{7,6},{9,4},{9,-4},{10,-1}};	
	//afficherTableau(tab);
	POINT *resultat=malloc(NB_POINTS*sizeof(POINT));
	// resultat[nbPoints];
	resultat=triAbscisse(tab,NB_POINTS);
	afficherTableauPoint(resultat,NB_POINTS);
	double *critique=malloc((NB_POINTS/2)*sizeof(double));
	printf("---------------\n");
	critique=tableauValeurCritique(resultat,NB_POINTS);
	afficherTableauDouble(critique,NB_POINTS/2);
	quickSort(critique,0,NB_POINTS/2-1);
	printf("trie du tableau: \n");
	afficherTableauDouble(critique,NB_POINTS/2);
	printf("valeur médiane:%lf \n", mediane(critique,NB_POINTS/2) );

}



