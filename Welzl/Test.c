#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "fonctions_resolution_brute.h"
#include "fonctions_Welzl.h"


int main() {

  POINT p1 = {10,15};
  POINT p2 = {10,5};
  POINT p3 = {5,10};
  POINT p4 = {15,10};
  POINT p5 = {0,0};
  POINT points[] = {p1,p2,p3,p4,p5};
  clock_t now;
  now=0; 
  CERCLE *c=MINIDISK(points,5);
  printf("Time ellapsed: %lf \n",(double)(clock()-now)/CLOCKS_PER_SEC);
  fprintf(stderr,"centre(%d,%d) et diamètre %f \n",c->x,c->y,c->d);
  return 0;
}
