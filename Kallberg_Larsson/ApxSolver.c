#include "improved_pruning.h"
#include "updateball_methods.h"
#include <time.h>
#include "../resolution_brute.h"

int rand_a_b (int a, int b){
  return rand()%(b-a )+a;
}

int main( int argc, char* argv []){
  int N, xmin , xmax, ymin, ymax;
  double apx; 

  srand(time(NULL));
  if (argc!=7 || atoi(argv[1])>500000){ //Plus de 600 000 points provoquent une segmentation fault
    printf("usage: %s <nbDePoints (inf. à 500000)> <xmin> <xmax> <ymin> <ymax> <precision (inf. à 1)>\n\n", argv[0]); 
    return 1;
  }

  N=atoi(argv[1]);
  printf ("\n%d points \n", N); //Affichage nb de points générés
  POINT tab[N];
	

  xmin=atoi(argv[2]);   
  xmax=atoi(argv[3]);
  ymin=atoi(argv[4]);
  ymax=atoi(argv[5]);
  apx=atof(argv[6]);

  int i;

  for (i=0;i<N;i++){
    tab[i].x =rand_a_b(xmin,xmax);
    tab[i].y =rand_a_b(ymin,ymax);
    printf("Point %d {%lf , %lf}\n",i,tab[i].x,tab[i].y );
  }

  printf("Algorithme de mise à jour utilisé: ");
  switch(MODE){
      case 1: 
        printf("BadoiuClarkson (MODE 1)\n");
        break;
      case 2: 
        printf("KallbergLarsson (MODE 2)\n");
        break;
      default: 
        exit(-1);
    }



  printf("\n__ ApxMEB1:");

  clock_t now;
  now=0;
	CERCLE c1 = ApxMEB1(tab , N , apx);
  printf("Time ellapsed: %lf\n", (double) (clock() - now) / CLOCKS_PER_SEC);
  printf("Centre ( %lf , %lf ) diamètre %lf\n", c1.x , c1.y , c1.d );
  
  printf("\n__ ApxMEB2:");

	now=0;
  CERCLE c2 = ApxMEB2(tab , N , apx);
  printf("Time ellapsed: %lf\n", (double) (clock() - now) / CLOCKS_PER_SEC);
  printf("Centre ( %lf , %lf ) diamètre %lf\n", c2.x , c2.y , c2.d );

  printf("\n__ BRUTE:\n");

  now=0;
  CERCLE c3 = brute(tab,N);
  printf("Time ellapsed: %lf\n", (double) (clock() - now) / CLOCKS_PER_SEC);
  printf("Centre ( %lf , %lf ) diamètre %lf\n", c3.x , c3.y , c3.d );
 

  printf("\n__ Comparaison:\n\n");
  printf("On veut r <= (1 + apx)r*  où r* est le rayon du vrai cercle englobant minimum.\n");
  printf("On a ici r=%lf par ApxMEB1 et r=%lf par ApxMEB2, or (1+apx)r*=%lf par méthode brute. \n",c1.d/2,c2.d/2,(1+apx)*c3.d/2);


	return 0;
}
