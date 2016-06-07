#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include "structures.h"
#include "fonctions_resolution_brute.h"
#include "resolution_brute.h"

#define TAILLEPOINT 3 //Diametre d'un point
#define N 50 //Nb de points


POINT* convertirEntree ();
int tailleFrame(int xf, int yf);
char* dessinerCercle(FILE *file, int x, int y, int r);
char* dessinerPoint(FILE *file, int x, int y, int r);
void ecritureSVG(POINT tab[N], FILE* file);
void GenerationFichierSVG(POINT tab[]);


int i=0, j=0;
int xf=0, yf=0; //coordonnés maximales qui serviront à calculer la taille de la frame
int a; //taille de la frame

//convertit les coordonnées de l'entrée standard en un tableau de POINTS
POINT* convertirEntree (){
  POINT* tab=malloc (sizeof(POINT)*N);
  char chaine[10];
  for (i;i<N;i++){
    while((chaine[j] = getc(stdin)) != ' ' && chaine[j]!=EOF){
      j++;
    }
    printf("%s ", chaine);
    tab[i].x=atoi(chaine);
    if(abs(tab[i].x)>xf){
      xf=abs(tab[i].x);
    }
    strcpy(chaine, "");
    j=0;
    while((chaine[j]= getc(stdin)) != '\n' && chaine[j]!=EOF){
      j++;
    }
    printf("%s\n", chaine);
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
  printf("%d %d\n",xf,yf);
  int a = sqrt(xf*xf+yf*yf);
  return a;
}

//dessine un cercle en SVG
char* dessinerCercle(FILE *file, int x, int y, int r){
  char* codeCercle= malloc (sizeof (*codeCercle) *500);
  sprintf(codeCercle,"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"red\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}


//Dessine un point en SVG
char* dessinerPoint(FILE *file, int x, int y, int r){ 
  char* codePoint= malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"black\" stroke-width=\"3\" fill=\"black\"/>",x,y,r);
  fprintf(file,"%s\n", codePoint);
  return codePoint;
}

//Dessine les points et le cercle dans le SVG
void ecritureSVG(POINT tab[N], FILE* file){
  //On dessine tous les points dans le SVG
  for(i=0; i<N; i++){
    dessinerPoint(file,(tab[i]).x, tab[i].y, TAILLEPOINT);
  }
  //On dessine le cercle dont le diametre correspon à la Frame (carrée) dans le SVG
  CERCLE CercleFrame;
  CercleFrame.x = a/2;
  CercleFrame.y=a/2;
  CercleFrame.d =a/2;


  //On calcul la solution brute puis on la dessine dans le SVG
  CERCLE CercleSolution=brute(tab , N);
  printf("x=%d, ",CercleSolution.x);
  printf("y=%d, ",CercleSolution.y);
  printf("r=%d\n",CercleSolution.d);
  printf("x=%d, ",CercleFrame.x);
  printf("y=%d, ",CercleFrame.y);
  printf("r=%d\n",CercleFrame.d);
  dessinerCercle(file, CercleFrame.x, CercleFrame.y, CercleFrame.d);
  dessinerCercle(file, CercleSolution.x, CercleSolution.y, CercleSolution.d);
}


//Genere le fichier SVG complet
void GenerationFichierSVG(POINT tab[]){
  //creation et ouverture du fichier
  FILE *file;
  file= fopen("Points.svg", "w");
  
  //ecriture de l'entete
  fprintf(file,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  fprintf(file,"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
  fprintf(file,"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
  fprintf(file,"<svg width=\"%d\" height=\"%d\" version=\"1.1\"\n",a,a);
  fprintf(file,"xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(file,"<title> RESOLUTION BRUTE </title>\n");
  fprintf(file,"<desc> Du RESOLUTION BRUTE. </desc>\n");
  
  //ecriture du programme
  ecritureSVG(tab,file);
  
  //fin du programme et fermer le fichier
  fprintf(file, "</svg>\n");
  fclose(file);
}

int main(){
  POINT *tab=convertirEntree();
  GenerationFichierSVG(tab);
  return 0;
}
