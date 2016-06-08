#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include "structures.h"


int argmax(POINT point, POINT* tab, int N);
double distance(POINT point1, POINT point2);
CERCLE SimpleIterativeBall(POINT*tab, int N, float e);
void display(POINT* tab, int N);

/**
 * Cherche l'argument m pour lequel le point tab[m] est le plus éloigné du point en entree
 * @param point un POINT
 * @param tab un tableau de POINT
 * @param N le nombre de points dans tab
 * @return l'argument recherché
**/
int argmax(POINT point, POINT* tab, int N){
  int i, d, r=0, m;
  for(i=0;i<N;i++){
    d=distance(point, tab[i]);
    if(d>r){
      m=i;
      r=d;
    }
  }
  return m; 
}

/**
 * Calcul la distance entre deux POINT
 * @param point1 un POINT
 * @param point2 un POINT
 * @return la distance entre les points
**/
double distance(POINT point1, POINT point2){
  double d=sqrt(pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2));
  return d;
}

/**
 * Affiche un tableau de points de taille N
 * @param tab le tableau de points
 * @param N le nombre de points
**/
void display(POINT* tab, int N){
  int i;
  for(i=0;i<N;i++){
    printf("xm=%lf", tab[i].x);  
    printf("ym=%lf", tab[i].y); 
    printf("i=%d\n", i);
  }
}

/**
 * Cherche un approximation du plus petit disque englobant un nombre de points donnes, à un facteur e pres
 * @param tab un tableau de POINT
 * @param N le nombre de points dans tab
 * @param e la précision de l'approximation
 * @return l'argument recherché
**/
CERCLE SimpleIterativeBall(POINT*tab, int N, float e){
  int i, m;
  double a;
  CERCLE cercle;
  POINT centre;

  centre.x=tab[0].x;
  centre.y=tab[0].y;

  i=1;
  a=1/(e*e);

  while(i<=a){
    m=argmax(centre, tab, N);
    centre.x+=((tab[m].x-centre.x)/(1+i));
    centre.y+=((tab[m].y-centre.y)/(1+i));
    i++;
  }
  cercle.x=centre.x;
  cercle.y=centre.y;
  cercle.d=2*distance(centre, tab[m]);
  return cercle; 
}
