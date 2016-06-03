#include "utils_table.h"



/*-------------------------------Traitement sur les tableaux----------------------------------------------*/

/*
affiche tableau de POINT
*/
void afficherTableauPoint(POINT tab[],int taille){
	//int taille=sizeof(tab)/sizeof(POINT);

	for (int i = 0; i <taille; ++i)
	{
		printf("%d | x = %lf | y = %lf ",i,tab[i].x,tab[i].y );
		printf("|\n");
	}
}
/*
affiche tableau de double
*/
void afficherTableauDouble(double tab[],int taille){
	//int taille=sizeof(tab)/sizeof(POINT);

	for (int i = 0; i <taille; ++i)
	{
		printf("%d | xcritique = %lf ",i,tab[i] );
		printf("|\n");
	}
}

/*Echange 2 valeurs d'un tableau
utile pour le quickSort
*/
void echanger(double tableau[], int a, int b){

    double temp = tableau[a];

    tableau[a] = tableau[b];

    tableau[b] = temp;

}

/*Trie le tableau*/

void quickSort(double tableau[], int debut, int fin){

    int gauche = debut-1;
    int droite = fin+1;
	const double pivot = tableau[debut];

    if(debut >= fin)
        return;

    while(1){

        do droite--; while(tableau[droite] > pivot);
        do gauche++; while(tableau[gauche] < pivot);

        if(gauche < droite)
            echanger(tableau, gauche, droite);
        else break;
    }
    quickSort(tableau, debut, droite);
    quickSort(tableau, droite+1, fin);
}

double mediane(double tableau[],int longueur){
    double valeur;
    if (longueur%2 == 0){
        valeur=((tableau[longueur/2]+tableau[(longueur/2)+1])/2);
        return valeur;
    }
    else{
        valeur=(tableau[(longueur+1)/2]);
        return valeur;
    }
}

