#include <stdio.h>
#include <stdlib.h> 
#include "structures.h"
#include <string.h>
#define taille 500
#define taillePoint 3


int i;
/*char * saisir_chaine(char * lpBuffer, size_t nBufSize){
  size_t nbCar = 0;    
  int c;
  c = getchar();
  while (nbCar < nBufSize - 1 && c != EOF && c != '\n'){
    lpBuffer[nbCar] = (char)c;
    nbCar++;
    c = getchar();
  }
  lpBuffer[nbCar] = '\0'; 
  return lpBuffer;
}*/



POINT* convertir (FILE* file){
	POINT* tab=malloc (sizeof (POINT) * taille);
	file= fopen("Points.txt","r");
	if(!file) {
    perror("File opening failed");
    exit;
  }
  int c;
	char *chaine;
	while((c = fgetc(file)) != EOF){
  	chaine=chaine+c;
		while((c = fgetc(file)) != ' ' && c!=EOF){
			chaine=chaine+c;
		}
		tab[i].x=atoi(chaine);
		strcpy(chaine, "");
		while((c = fgetc(file)) != ' ' && c!=EOF){
			chaine=chaine+c;
		}
		tab[i].y=atoi(chaine);
		strcpy(chaine, "");
		i++;
	}
	return tab;
}


char* dessinerCercle(int x, int y, int r){
  char* codeCercle= malloc (sizeof (*codeCercle) *500);
  sprintf(codeCercle,"<circle x=\"%d\" y=\"%d\" r=\"%d\" stroke=\"black\" stroke-width=\"3\" fill=\"red\" />",x,y,r);
  printf("%s\n", codeCercle);
  return codeCercle;
}



char* dessinerPoint(int x, int y, int r){ 
  char* codePoint= malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle x=\"%d\" y=\"%d\" r=\"%d\" stroke=\"black\" stroke-width=\"3\"/>",x,y,r);
  printf("%s\n", codePoint);
  return codePoint;
}


void ecritureSVG(POINT tab[taille], FILE* file){
  for(i=0; i<taille; i++){
		fprintf(file,dessinerPoint((tab[i]).x, tab[i].y, taillePoint));
  }
  //calcul du cercle
  //fprintf(file,dessinerCercle(cercle.x,cercle.y,cercle.r);

}



void fichierSVG(POINT tab[]){
  //creation et ouverture du fichier
  FILE *file;
  file= fopen("Points.svg", "a");
  
  //ecriture de l'entete
  fprintf(file,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  fprintf(file,"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
  fprintf(file,"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
  fprintf(file,"<svg width=\"500\" height=\"500\" version=\"1.1\"\n");
  fprintf(file,"xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(file,"<title> EXEMPLE LOGO </title>\n");
  fprintf(file,"<desc> Du LOGO. </desc>\n");
  
  //ecriture du programme
  ecritureSVG(tab,file);

  //fin du programme et fermer le fichier
  fprintf(file, "</svg>\n");
  fclose(file);
}




int main(){
  char lpBuffer[taille];
	FILE *file;
  //lpBuffer=saisir_chaine(lpBuffer, sizeof(lpBuffer));
  POINT *tab=convertir(file);
	FichierSVG(tab);
  printf("Chaine enregistrée: %s\n", lpBuffer);
  dessinerPoint(50,50,50);
  dessinerCercle(50,50,50);
  
  return 0;
}
