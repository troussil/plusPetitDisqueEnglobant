
#include "fonction_megiddo.h"
#include "structure.h"
#include "utils_table.h"
#include "solveur_megiddo.h"

int main(int argc, char* argv []){
	if(argc!=2){
		printf("%s :Nombre invalide d'arguments\n",argv[0]);
		printf("usage: %s <nbDePoints>\n", argv[0]); 	
		return 1;
	}

  char nbPointsStr[10]; //Contiendra les caractères lus pour le nb de points
  int k = 0;

  while((nbPointsStr[k] = getc(stdin)) != ' ' && nbPointsStr[k]!=EOF){
      k++;
  }
  

  int nbPoints = atoi(nbPointsStr);
  printf("\n*\nNombre de points lu: %s \n*\n", nbPointsStr);
  
  POINT *tab = convertirEntree( nbPoints );
  printf("*\nPoints lus sur le stdin et convertis !\n*\n");

	//POINT tab[NB_POINTS] = {{2,1},{3,-3},{5,4},{6,2},{7,-1},{7,-2},{8,2},{8,5},{9,-4},{10,-1},{10,3},{12,-2}};	
	//afficherTableau(tab);
	// int resultat;
	int new_point=atoi(argv[1]);
	int compteur=1;
	// printf("size of resultat %d\n",sizeof(tab)/sizeof(POINT));
	// printf("size of POINT %d\n",sizeof(POINT));
	//POINT resultat[9]=pruning(tab,NB_POINTS);
	//new_point=pruning(tab,40);
	while(new_point>8){
		new_point=pruningContraint(tab,new_point,0);
		printf("après élagage %d\n",compteur);
		compteur+=1;
		afficherTableauPoint(tab,new_point);
	}
	printf("new_point= %d\n",new_point );
	printf("---------------------\n");
	return 1;
	
	

	


	//quickSortPoint(tab,0,9);
	//afficherTableauPoint(tab,NB_POINTS);
	// resultat[nbPoints];

	//DOUBLET *critique=malloc((NB_POINTS/2)*sizeof(DOUBLET));
	//printf("---------------\n");
	//critique=tableauValeurCritique(resultat,NB_POINTS);
	//afficherTableauDoublet(critique,NB_POINTS/2);
	//quickSortDoublet(critique,0,NB_POINTS/2-1);
	//printf("trie du tableau: \n");
	//afficherTableauDoublet(critique,NB_POINTS/2);
	//printf("valeur médiane:%lf \n", mediane(critique,NB_POINTS/2));
	//printf("pruning...\n");
	//prune=pruning(prune,critique,NB_POINTS);
	//afficherTableauPoint(prune,NB_POINTS*(3/4));


}



