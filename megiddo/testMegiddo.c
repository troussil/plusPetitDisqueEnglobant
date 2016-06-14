
#include "fonction_megiddo.h"
#include "structure.h"
#include "utils_table.h"
#include "utils.h"

int main(int argc, char* argv []){
  
	POINT tab[NB_POINTS] = {{2,1},{3,-3},{4,0},{3,4},{7,-1},{5,-2},{8,2},{3,5},{9,-4},{10,-1},{12,3},{11,3}};	
	//afficherTableau(tab);
	// int resultat;
	//int new_point=NB_POINTS;
	//int compteur=1;
	// printf("size of resultat %d\n",sizeof(tab)/sizeof(POINT));
	// printf("size of POINT %d\n",sizeof(POINT));
	//POINT resultat[9]=pruning(tab,NB_POINTS);
	//new_point=pruning(tab,40);
	// while(new_point>3){
	// 	new_point=pruning(tab,new_point,0);
	// 	printf("après élagage %d\n",compteur);
	// 	compteur+=1;
	// 	afficherTableauPoint(tab,new_point);
	// }
	// printf("new_point= %d\n",new_point );
	// printf("---------------------\n");
	// DOUBLET *d1=malloc(sizeof(DOUBLET));
	// DOUBLET *d2=malloc(sizeof(DOUBLET));
	DOUBLET *critique=malloc((NB_POINTS)*sizeof(DOUBLET));
	POINT *intersection=malloc((NB_POINTS/4)*sizeof(POINT));
	printf("intersections: \n");
	critique=calculAngleCritique(tab,NB_POINTS);
	intersection=intersectionLigne(critique,6);
	afficherTableauPoint(intersection,3);

	// d1->a=tab[0];
	// d1->b=tab[1];
	// d2->a=tab[2];
	// d2->b=tab[3];
	// calculDroite(d1,1);
	// afficherTableauDroite(d1,1);
	// calculDroite(d2,1);
	// afficherTableauDroite(d2,1);
	// if(estParallele(*d1,*d2)==1){
	// 	printf("droite parallele, pas d'intersection\n");
	// }else{
	// 	intersection=calculIntersection(*d1,*d2);
	// afficherTableauPoint(intersection,1);
	// }





	//quickSortPoint(tab,0,9);
	//afficherTableauPoint(tab,NB_POINTS);
	// resultat[nbPoints];
	// double angle;
	// DOUBLET *critique=malloc((NB_POINTS/2)*sizeof(DOUBLET));
	// //printf("---------------\n");
	// critique=calculAngleCritique(tab,NB_POINTS);
	// angle=quickSortDoubletAngle(critique,0,NB_POINTS/2-1);
	// calculDroite(critique,NB_POINTS/2);
	// afficherTableauDroite(critique,NB_POINTS/2);
	// printf("angle médian: %lf\n",angle );
	//quickSortDoublet(critique,0,NB_POINTS/2-1);
	//printf("trie du tableau: \n");
	//afficherTableauDoublet(critique,NB_POINTS/2);
	//printf("valeur médiane:%lf \n", mediane(critique,NB_POINTS/2));
	//printf("pruning...\n");
	//prune=pruning(prune,critique,NB_POINTS);
	//afficherTableauPoint(prune,NB_POINTS*(3/4));

	return 1;

}



