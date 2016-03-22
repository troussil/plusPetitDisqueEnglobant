#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cadre.h"

int rand_a_b (int a, int b){
  return rand()%(b-a )+a;
}

int main( int argc, char* argv []){
  int N, xmin , xmax, ymin, ymax; //N=nb  de points et coordonnées du cadre 
  srand(time(NULL));
  if (argc!=6){
    printf ("erreur, nb invalide d'arguments");
    return(-1);
   }
   N=atoi(argv[1]);
   xmin=atoi(argv[2]);
   xmax=atoi(argv[3]);
   xmin=atoi(argv[4]);
   xmax=atoi(argv[5]);
   Point tableau [N];// tableau de points
   int i;
   for (i=0;i<N;i++){
    tableau[i].x=rand_a_b(xmin,xmax);
    tableau[i].y=rand_a_b(ymin,ymax);
    printf ("point %d de cooordonnées (%d,%d)\n",i,tableau[i].x,tableau[i].y);
   }
}
