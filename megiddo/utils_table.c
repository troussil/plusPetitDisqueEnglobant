#include "utils_table.h"



/*-------------------------------Traitement sur les tableaux----------------------------------------------*/

/*
affiche tableau de POINT
*/
void afficherTableauPoint(POINT tab[],int taille){
	//int taille=sizeof(tab)/sizeof(POINT);
    int i;
	for ( i = 0; i <taille; i++)
	{
		printf("%d | x = %lf | y = %lf ",i,tab[i].x,tab[i].y );
		printf("|\n");
	}
}
/*
affiche tableau de double
*/
void afficherTableauDoublet(DOUBLET tab[],int taille){
	//int taille=sizeof(tab)/sizeof(POINT);
    int i;
	for ( i = 0; i <taille; i++)
	{
		printf("doublet: %d | xi= %lf | yi= %lf | xj= %lf | yj= %lf | xcritique = %lf ",i,tab[i].a.x,tab[i].a.y,tab[i].b.x,tab[i].b.y ,tab[i].mediatrice);
		printf("|\n");
	}
}

/*Echange 2 valeurs d'un tableau
utile pour le quickSort
*/
void echanger(DOUBLET tableau[], int a, int b){

    POINT *tempA=malloc(sizeof(POINT));
    POINT *tempB=malloc(sizeof(POINT));
    double temp = tableau[a].mediatrice;
    *tempA=tableau[a].a;
    *tempB=tableau[a].b;

    tableau[a].mediatrice = tableau[b].mediatrice;
    tableau[a].a=tableau[b].a;
    tableau[a].b=tableau[b].b;

    tableau[b].mediatrice = temp;
    tableau[b].a=*tempA;
    tableau[b].b=*tempB;

}

/*Trie le tableau
Problème : complexité en nlog(n)....
A voir plus tard
*/

void quickSort(DOUBLET tableau[], int debut, int fin){

    int gauche = debut-1;
    int droite = fin+1;
	const double pivot = tableau[debut].mediatrice;

    if(debut >= fin)
        return;

    while(1){

        do droite--; while(tableau[droite].mediatrice > pivot);
        do gauche++; while(tableau[gauche].mediatrice < pivot);

        if(gauche < droite)
            echanger(tableau, gauche, droite);
        else break;
    }
    quickSort(tableau, debut, droite);
    quickSort(tableau, droite+1, fin);
}

/*Calcul de la valeur médiane d'un tableau*/

double mediane(DOUBLET tableau[],int longueur){
    double valeur;
    if (longueur%2 == 0){
        valeur=(((tableau[(longueur/2)-1].mediatrice)+(tableau[(longueur/2)].mediatrice))/2);
        return valeur;
    }
    else{
        valeur=((tableau[((longueur+1)/2)-1].mediatrice));
        return valeur;
    }
}

