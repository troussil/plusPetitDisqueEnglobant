#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "fonctions_resolution_brute.h"
#include "fonctions_Welzl.h"
#include <time.h>


//bien se rappeler pour la presentation finale d'expliquer en quoi c'est un algo de complexité lineaire en esperance, et non pas deterministe.(c'est pas evident)
//et BIEN montrer et expliquer la recursivité, pas seulement dans l'algo mais concretement



void randomisationTableau(POINT *P, int tailleP){
    int i=0;
    int nombre_tire=0;
    POINT temp;
    for(i = 0; i< tailleP;i++){
        nombre_tire=rand()%tailleP;
        // On échange les contenus des cases i et nombre_tire
        temp = P[i];
        P[i] = P[nombre_tire];
        P[nombre_tire]=temp;
    }
}  

int Pointrand (int tailleP){
  return tailleP-1; //index du point, avec tailleP taille du tableau P

}

CERCLE *b_md(POINT *R,int casesRemplies){
  if(casesRemplies==0){
    CERCLE *C;
    C = malloc (sizeof(CERCLE));
    return C;
  }  
  if(casesRemplies==1){
    CERCLE *C;
    C = malloc (sizeof(CERCLE));
    C->d=0;
    C->x=R[0].x;
    C->y=R[0].y;
    return C;
  }   
  if(casesRemplies==2)
    return cerclePassantParDeuxPoints(R[0],R[1]);
  if(casesRemplies==3)
    return cerclePassantParTroisPoints(R[0],R[1],R[2]);
  else{
    printf("error");
  }
}    

int defined(CERCLE *C,POINT *P,int taille){
  int ok=contientTousPoint(C,P,taille);
  return ok;

}  

CERCLE *B_MINIDISK(POINT *P,POINT *R,int tailleP,int tailleR){
  CERCLE *D;
  D = malloc (sizeof(CERCLE));
  if((tailleP==0) || (tailleR==3))
    D=b_md(R,tailleR);
  else{    
    int index=Pointrand(tailleP);
    POINT point=P[index];
    D= B_MINIDISK(P,R,tailleP-1,tailleR);
    if (contientPoint(D,point)==0){//si le point n'est pas dans le cercle
      R[tailleR]=point;
      D=B_MINIDISK(P,R,tailleP-1,tailleR+1);
    }
  }
  return D;    
}

CERCLE *MINIDISK(POINT *P,int tailleP){
  POINT *R;
  R=malloc (sizeof(POINT));
  randomisationTableau(P,tailleP);
  return B_MINIDISK(P,R,tailleP,0);
}

  
