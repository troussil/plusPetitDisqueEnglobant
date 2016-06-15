#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include "structures.h"


int argmax(POINT point, POINT* tab, int N);
int argmax2(POINT point, POINT* tab, int N);
double distance(POINT point1, POINT point2);
CERCLE SimpleIterativeBall(POINT*tab, int N, double e);
void display(POINT* tab, int N);
void calculNorme (POINT* tab, int N);
CERCLE ApproximateCoreSet(POINT*tab, int N, double e);
double distanceCoreSet(POINT point, POINT *tab, int N);

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
double distanceCoreSet(POINT point, POINT *tab, int N){
  int i;
  double distanceMax=0, distanceCourante;
  for (i=1;i<N;i++){
    distanceCourante=distance(tab[i],point);
    if(distanceCourante>distanceMax){
      distanceMax=distanceCourante;
      //printf("d2=%lf\n",distanceMax);
    }
  //printf("distcourante=%lf\n",distanceCourante);
  }
  return distanceMax;
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
 * @return une approximation du plus petit cercle englobant
**/
CERCLE SimpleIterativeBall(POINT*tab, int N, double e){
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
 * @return une approximation du plus petit cercle englobant
**/
CERCLE ApproximateCoreSet(POINT*tab, int N, double e){
  double gama=e/3, delta=e/3, rayon=0;
  int i=1, k;
  CERCLE cercle;
  POINT* tabIteratif=malloc (sizeof(POINT)*N); tabIteratif[0]=tab[0];
  POINT centre; centre.x=tab[0].x; centre.y=tab[0].y;
  
  while(distanceCoreSet(centre,tab,N)>=(1+delta)*rayon){
    k=argmax(centre, tab, N);
    tabIteratif[i]=tab[k];
    cercle=SimpleIterativeBall(tabIteratif,i+1,gama);
    centre.x=cercle.x;
    centre.y=cercle.y;
    rayon=cercle.d/2;
    printf("i=%d gama=%lf \ncercle.x=%lf cercle.y=%lf cercle.d=%lf\n", i, gama, cercle.x, cercle.y, cercle.d);
    printf("centre.x=%lf centre.y=%lf rayon=%lf\n", centre.x, centre.y, rayon);
    i++;
  }
  return cercle;
}
