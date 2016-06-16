#include "solveur_megiddo.h"
#include "solution_brute_contrainte.h"
#include "fonction_megiddo.h"
#include <math.h>


int i=0, j=0;

/*
 * Convertit les coordonnées de l'entrée standard en un tableau de POINTS
 * @param N nombre de points
*/

POINT* convertirEntree (int N){
  POINT* tab=malloc (sizeof(POINT)*N);
  char chaine[10];
  for (i=0;i<N;i++){
    while((chaine[j] = getc(stdin)) != ' ' && chaine[j]!=EOF){
      j++;
    }
    /* printf("%s ", chaine); */
    tab[i].x=atoi(chaine);
   // printf("%lf ", tab[i].x); 
    strcpy(chaine, "");
    j=0;
    while((chaine[j]= getc(stdin)) != '\n' && chaine[j]!=EOF){
      j++;
    }
    /* printf("%s\n", chaine); */
    tab[i].y=atoi(chaine);
    //printf("%lf\n", tab[i].y); 
    strcpy(chaine, "");
    j=0;
  }
  return tab;
}

//dessine un cercle en SVG
char* dessinerCercleBrute(FILE *file,CERCLE c){
  char* codeCercle= malloc (sizeof (*codeCercle) *500);
  sprintf(codeCercle,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"red\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",c.centre.x,c.centre.y,c.d);
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}

char* dessinerCercleAmeliore(FILE *file,CERCLE c){
  char* codeCercle= malloc (sizeof (*codeCercle) *500);
  sprintf(codeCercle,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"green\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",c.centre.x,c.centre.y,c.d);
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}



//Dessine un point en SVG
char* dessinerPoint(FILE *file, double x, double y, int r){ 
  char* codePoint= malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%d\" stroke=\"black\" stroke-width=\"3\" fill=\"black\"/>",x,y,r);
  fprintf(file,"%s\n", codePoint);
  return codePoint;
}

//Dessine les points et le cercle dans le SVG
void ecritureSVG(POINT tab[], FILE* file , int N,int yc){
  //On dessine tous les points dans le SVG
  for(i=0; i<N; i++){
    dessinerPoint(file,(tab[i]).x, tab[i].y, TAILLEPOINT);
  }
  //On calcul la solution brute puis on la dessine dans le SVG
  CERCLE *solutionbrute=malloc(sizeof(CERCLE));
  solutionbrute=solutionBruteContrainte(tab,N,yc);
  dessinerCercleBrute(file, *solutionbrute);

   printf(" \n*** CERCLE SOLUTION PAR METHODE BRUTE: posX = %lf , posY = %lf , diamètre = %lf  ***\n", solutionbrute->centre.x, solutionbrute->centre.y, solutionbrute->d );

/*-------ELAGAGE---------*/
   int new_point=N;
   while(new_point>15){
    new_point=pruningContraint(tab,new_point,0);
  }
  CERCLE *solutionAmeliore=malloc(sizeof(CERCLE));
  solutionAmeliore=solutionBruteContrainte(tab,new_point,yc);
  dessinerCercleAmeliore(file, *solutionAmeliore);

}


//Genere le fichier SVG complet
void GenerationFichierSVG(POINT tab[] , int N,int yc){
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
  ecritureSVG(tab,file,N,yc);
  
  //fin du programme et fermer le fichier
  fprintf(file, "</svg>\n");
  fclose(file);
}

int main(){
  
  char nbPointsStr[10]; //Contiendra les caractères lus pour le nb de points
  int k = 0;

  while((nbPointsStr[k] = getc(stdin)) != ' ' && nbPointsStr[k]!=EOF){
      k++;
  }
  

  int nbPoints = atoi(nbPointsStr);
  printf("\n*\nNombre de points lu: %s \n*\n", nbPointsStr);
  
  POINT *tab = convertirEntree( nbPoints );
  printf("*\nPoints lus sur le stdin et convertis !\n*\n");
  
  GenerationFichierSVG(tab , nbPoints,200);
  printf("*\nFichier SVG généré !  \n*\n");
  
  return 0;
}
