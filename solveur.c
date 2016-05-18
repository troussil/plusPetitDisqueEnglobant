#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "structures.h"
#include "fonctions_resolution_brute.h"
#include "resolution_brute.h"

#define TAILLEPOINT 3 //Diametre d'un point
#define N 10 //Nb de points


POINT* convertirEntree ();
char* dessinerCercle(FILE *file, int x, int y, int r);
char* dessinerPoint(FILE *file, int x, int y, int r);
void ecritureSVG(POINT tab[N], FILE* file);
void GenerationFichierSVG(POINT tab[]);


int i=0, j=0;

//convertit les coordonnées de l'entrée standard en un tableau de POINTS
POINT* convertirEntree (){
  POINT* tab=malloc (sizeof(POINT)*N);
  char chaine[10];
  for (i=0;i<N;i++){
    while((chaine[j] = getc(stdin)) != ' ' && chaine[j]!=EOF){
      j++;
    }
    /* printf("%s ", chaine); */
    tab[i].x=atoi(chaine);
    printf("%d ", tab[i].x); 
    strcpy(chaine, "");
    j=0;
    while((chaine[j]= getc(stdin)) != '\n' && chaine[j]!=EOF){
      j++;
    }
    /* printf("%s\n", chaine); */
    tab[i].y=atoi(chaine);
    printf("%d\n", tab[i].y); 
    strcpy(chaine, "");
    j=0;
  }
  return tab;
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
  //On calcul la solution brute puis on la dessine dans le SVG
  CERCLE CercleSolution=brute(tab , N);
  /*CERCLE CercleSolution;
  CercleSolution.x = 250;
  CercleSolution.y=250;
  CercleSolution.d = 250;*/
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
  fprintf(file,"<svg width=\"500\" height=\"500\" version=\"1.1\"\n");
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
