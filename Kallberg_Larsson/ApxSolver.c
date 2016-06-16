#include "improved_pruning.h"
#include "updateball_methods.h"
#include <time.h>
#include "../resolution_brute.h"
#include "../fonctions_resolution_brute.h"

int rand_a_b (int a, int b){
  return rand()%(b-a )+a;
}

int main( int argc, char* argv []){
  
  int N, xmin , xmax, ymin, ymax;
  double apx; 
  int mode = 1;

  srand(time(NULL));
  if (argc!=8 || atoi(argv[2])>500000){ //Plus de 600 000 points provoquent une segmentation fault
    printf("usage: %s <update mode> <nbDePoints (inf. à 500000)> <xmin> <xmax> <ymin> <ymax> <precision (inf. à 1)>\n\n", argv[0]); 
    return 1;
  }

  
  
	
  mode=atoi(argv[1]);
  N=atoi(argv[2]);
  xmin=atoi(argv[3]);   
  xmax=atoi(argv[4]);
  ymin=atoi(argv[5]);
  ymax=atoi(argv[6]);
  apx=atof(argv[7]);

  printf ("\n%d points \n", N); 

  POINT tab[N];
  int i;

  for (i=0;i<N;i++){
    tab[i].x =rand_a_b(xmin,xmax);
    tab[i].y =rand_a_b(ymin,ymax);
    //printf("Point %d {%lf , %lf}\n",i,tab[i].x,tab[i].y );
  }

  printf("Algorithme de mise à jour utilisé: ");
  switch(mode){
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
  printf("Englobe tous les points: ");
  if(contientTousPoint(c1,tab,N)){printf("Ok ✓\n");}else{printf("No ✗\n");}
  
  printf("\n__ ApxMEB2:");

	now=0;
  CERCLE c2 = ApxMEB2(tab , N , apx);
  printf("Time ellapsed: %lf\n", (double) (clock() - now) / CLOCKS_PER_SEC);
  printf("Centre ( %lf , %lf ) diamètre %lf\n", c2.x , c2.y , c2.d );
  printf("Englobe tous les points: ");
  if(contientTousPoint(c2,tab,N)){printf("Ok ✓\n");}else{printf("No ✗\n");}

  printf("\n__ BRUTE:\n");

  now=0;
  CERCLE c3 = brute(tab,N);
  printf("Time ellapsed: %lf\n", (double) (clock() - now) / CLOCKS_PER_SEC);
  printf("Centre ( %lf , %lf ) diamètre %lf\n", c3.x , c3.y , c3.d );
  printf("Englobe tous les points: ");
  if(contientTousPoint(c3,tab,N)){printf("Ok ✓\n");}else{printf("No ✗\n");}
 

  printf("\n__ Comparaison:\n");
  printf("On veut r <= (1 + apx)r*  où r* est le rayon du vrai cercle englobant minimum.\n");

  printf("(1+apx)r* = %lf     par méthode brute\n", (1+apx)*c3.d/2 );
  printf("    r     = %lf     par ApxMEB1 ",c1.d/2 );
  if (c1.d/2<=(1+apx)*c3.d/2)
    printf("    => Ok ✓\n");
  else
    printf("    => Fail ✗\n");
  printf("    r     = %lf     par ApxMEB2 ",c2.d/2 );
  if (c2.d/2<=(1+apx)*c3.d/2)
    printf("    => Ok ✓\n\n");
  else
    printf("    => Fail ✗\n\n");



	return 0;
}
