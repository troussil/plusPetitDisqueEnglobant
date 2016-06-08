#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include "structures.h"
#include "fonctions_resolution_brute.h"
#include "resolution_brute.h"
#include "NielsenKnock.h"
#include <time.h>

#define TAILLEPOINT 3 //Diametre d'un point



int tailleFrame(int xf, int yf);
POINT* convertirEntree ();
char* dessinerCercle(FILE *file, int x, int y, int r, char* couleur);
char* dessinerPoint(FILE *file, int x, int y, int r);
void ecritureSVG(POINT tab[], FILE* file , int N);
void GenerationFichierSVG(POINT tab[] , int N);


int i=0, j=0;
int xf=0, yf=0; //coordonnés maximales qui serviront à calculer la taille de la frame
int a; //taille de la frame
int nbPoints; //nb de points générés


/*
 * Convertit les coordonnées de l'entrée standard en un tableau de POINTS
*/
POINT* convertirEntree (){
  
  char nbPointsStr[10]; //Contiendra les caractères lus pour le nb de points
  int k = 0;


  while((nbPointsStr[k] = getc(stdin)) != ' ' && nbPointsStr[k]!=EOF){
    k++;
  }
  nbPoints = atoi(nbPointsStr);
  printf("\n*\nNombre de points lu: %d \n*\n", nbPoints);
  strcpy(nbPointsStr, "");

  POINT* tab=malloc (sizeof(POINT)*nbPoints);
  char chaine[10];
 
  for (i=0;i<nbPoints;i++){
    while((chaine[j] = getc(stdin)) != ' ' && chaine[j]!=EOF){
      j++;
    }
    tab[i].x=atoi(chaine);
    if(abs(tab[i].x)>xf){
      xf=abs(tab[i].x);
    }
    strcpy(chaine, "");
    j=0;
    while((chaine[j]= getc(stdin)) != '\n' && chaine[j]!=EOF){
      j++;
    }
    tab[i].y=atoi(chaine);
    if(abs(tab[i].y)>yf){
      yf=abs(tab[i].y);
    }
    strcpy(chaine, "");
    j=0;
  }

  a=tailleFrame(xf,yf); //mise a jour de la taille de la frame
  return tab;
}

//calcul la taille de la frame
int tailleFrame(int xf, int yf){
  printf("abcisse maximum : %d, ordonnée maximum: %d\n",xf,yf);
  int a = sqrt(xf*xf+yf*yf);
  return a;
}

//dessine un cercle en SVG
char* dessinerCercle(FILE *file, int x, int y, int r, char* couleur){
  char* codeCercle= malloc (sizeof (*codeCercle) *500);
  sprintf(codeCercle,"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"%s\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x+a/4,y+a/4,r,couleur);
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}


//Dessine un point en SVG
char* dessinerPoint(FILE *file, int x, int y, int r){ 
  char* codePoint= malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"black\" stroke-width=\"3\" fill=\"black\"/>",x+a/4,y+a/4,r);
  fprintf(file,"%s\n", codePoint);
  return codePoint;
}

//Dessine les points et le cercle dans le SVG
void ecritureSVG(POINT tab[], FILE* file , int N){
  //On dessine tous les points dans le SVG
  for(i=0; i<N; i++){
    dessinerPoint(file,(tab[i]).x, tab[i].y, TAILLEPOINT);
  }

/**********************************************************************************************************************************/
/**********************************************APPELS DES DIFFERENTS ALGOS*********************************************************/
/**********************************************************************************************************************************/

 
/****************************************************SOLUTION BRUTE****************************************************************/
   
/*
  CERCLE CercleSolution=brute(tab , N);
  printf("x=%d, ",CercleSolution.x);
  printf("y=%d, ",CercleSolution.y);
  printf("r=%lf\n",CercleSolution.d);
  dessinerCercle(file, CercleSolution.x, CercleSolution.y, CercleSolution.d/2,"red");

  printf(" \n*** CERCLE SOLUTION PAR METHODE BRUTE: posX = %d , posY = %d , diamètre = %lf  ***\n", CercleSolution.x, CercleSolution.y, CercleSolution.d );
  */

/****************************************************NIELSEN & KNOCK***************************************************************/

  double e =(0.01);
  CERCLE CercleNK=SimpleIterativeBall(tab , N, e);
  dessinerCercle(file, CercleNK.x, CercleNK.y, CercleNK.d/2,"blue");
  printf(" \n*** CERCLE SOLUTION PAR METHODE NIELSEN & KNOCK: posX = %lf , posY = %lf , diamètre = %lf  ***\n", CercleNK.x, CercleNK.y, CercleNK.d );
}

//Genere le fichier SVG complet
void GenerationFichierSVG(POINT tab[] , int N){
  //creation et ouverture du fichier
  FILE *file;
  file= fopen("Points.svg", "w");
  
  //ecriture de l'entete
  fprintf(file,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  fprintf(file,"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
  fprintf(file,"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
  fprintf(file,"<svg width=\"%d\" height=\"%d\" version=\"1.1\"\n",a*2,a*2);
  fprintf(file,"xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(file,"<title> Smallest enclosing Ball </title>\n");
  fprintf(file,"<desc> Smallest enclosing Ball </desc>\n");
  
  //ecriture du programme
  ecritureSVG(tab,file,N);
  
  //fin du programme et fermer le fichier
  fprintf(file, "</svg>\n");
  fclose(file);
}

int main(){
  time_t debut;
  debut = time(NULL);

  POINT *tab = convertirEntree();
  printf("*\nPoints lus sur le stdin et convertis !\n*\n");
  printf("TRAITEMENT...\n"); 
  GenerationFichierSVG(tab , nbPoints);
  printf("*\nFichier SVG généré !  \n*\n");

  printf("temps d'éxécution: %d sec\n", time(NULL)-debut);
  return 0;
}
