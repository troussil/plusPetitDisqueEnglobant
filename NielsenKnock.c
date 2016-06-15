#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include "structures.h"


int argmax(POINT point, POINT* tab, int N);
int argmax2(POINT point, POINT* tab, int N);
double distance(POINT point1, POINT point2);
CERCLE SimpleIterativeBall(POINT*tab, int N, float e);
void display(POINT* tab, int N);
void calculNorme (POINT* tab, int N);
CERCLE ApproximateCoreSet(POINT*tab, int N, float e);
double distanceCoreSet(POINT *tab1,int N1, POINT *tab2, int N2);

/**
 * Calcul la norme de tous les points d'un tableau de points donné et met à jour la structure de chaque point
 * @param tab un tableau de POINT
 * @param N le nombre de points dans tab
**/
void calculNorme (POINT* tab, int N){
  int i;
  for(i=0;i<N;i++){  
    tab[i].norme=tab[i].x*tab[i].x+tab[i].y*tab[i].y;
  }
}

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
 * Cherche l'argument m pour lequel le point tab[m] est le plus éloigné du point en entree en utilisant CAUCHY-SCHWARTZ
 * @param point un POINT
 * @param tab un tableau de POINT
 * @param N le nombre de points dans tab
 * @return l'argument recherché
**/
int argmax2(POINT point, POINT* tab, int N){
  int i, argMax;
  double distanceCourante, distanceMax=0; 
  for(i=0;i<N;i++){
    if(sqrt(tab[i].norme+point.norme+2*sqrt(tab[i].norme*point.norme))>distanceMax){
      distanceCourante=distance(point, tab[i]);
      if(distanceCourante>distanceMax){
        argMax=i;
        distanceMax=distanceCourante;
      }
    }
  }
  return argMax; 
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
 * Calcul la distance entre deux ensembles de POINT
 * @param tab1 et tab2 des tableaux de points
 * @param N1 et N2 les tailles respectives des tableaux tab1 et tab2
 * @return la distance entre les deux ensembles de POINT
**/
double distanceCoreSet(POINT *tab1,int N1, POINT *tab2, int N2){
  int i, j;
  double distanceMin=distance(tab1[0],tab2[0]), distanceCourante;
  for (i=0;i<N1;i++){
    for (j=0;j<N2;j++){
      if(distanceCourante=distance(tab1[i],tab2[j])<distanceMin){
        distanceMin=distanceCourante;
      }
    }
  }
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

  calculNorme(tab,N);

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

/**
 * Cherche un approximation du plus petit disque englobant un nombre de points donnes, à un facteur e pres
 * @param tab un tableau de POINT
 * @param N le nombre de points dans tab
 * @param e la précision de l'approximation
 * @return l'argument recherché
*
CERCLE ApproximateCoreSet(POINT*tab, int N, float e){
  double gama=e/3, delta=e/3, rayon=0;
  int i=1, k;
  CERCLE cercle;
  POINT* C1=malloc (sizeof(POINT)*N);
  C1[0]=tab[0];
  centre.x=tab[0].x;
  centre.y=tab[0].y;
  
  while(distanceCOREsET(centre,tab)>=(1+delta)*rayon){
    k=argmax2
  
  
}
*/
