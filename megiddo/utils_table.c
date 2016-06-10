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
		printf("doublet: %d | xi= %lf | yi= %lf | xj= %lf | yj= %lf | xcritique = %lf | angle en radian= %lf",i,tab[i].a.x,tab[i].a.y,tab[i].b.x,tab[i].b.y ,tab[i].mediatrice,tab[i].angle);
		printf("|\n");
	}
}

/*Echange 2 valeurs d'un tableau
utile pour le quickSort
*/
void echangerDoublet(DOUBLET tableau[], int a, int b){

    POINT *tempA=malloc(sizeof(POINT));
    POINT *tempB=malloc(sizeof(POINT));
    double tempMed = tableau[a].mediatrice;
    double tempAngle= tableau[a].angle;
    *tempA=tableau[a].a;
    *tempB=tableau[a].b;

    tableau[a].mediatrice = tableau[b].mediatrice;
    tableau[a].angle=tableau[b].angle;
    tableau[a].a=tableau[b].a;
    tableau[a].b=tableau[b].b;

    tableau[b].mediatrice = tempMed;
    tableau[b].angle=tempAngle;
    tableau[b].a=*tempA;
    tableau[b].b=*tempB;

}

void echangerPoint(POINT tableau[], int a, int b){

    double tempX=tableau[a].x;
    double tempY=tableau[a].y;

    tableau[a].x=tableau[b].x;
    tableau[a].y=tableau[b].y;

    tableau[b].x=tempX;
    tableau[b].y=tempY;

}



/*Trie le tableau
Problème : complexité en nlog(n)....
A voir plus tard
*/

double quickSortDoubletMediatrice(DOUBLET tableau[], int debut, int fin){

    int gauche = debut-1;
    int droite = fin+1;
	const double pivot = tableau[debut].mediatrice;

    if(debut >= fin){
        return medianeMediatrice(tableau,fin+1);

    }
        

    while(1){

        do droite--; while(tableau[droite].mediatrice > pivot);
        do gauche++; while(tableau[gauche].mediatrice < pivot);

        if(gauche < droite)
            echangerDoublet(tableau, gauche, droite);
        else break;
    }
    quickSortDoubletMediatrice(tableau, debut, droite);
    quickSortDoubletMediatrice(tableau, droite+1, fin);
}

double quickSortDoubletAngle(DOUBLET tableau[], int debut, int fin){

    int gauche = debut-1;
    int droite = fin+1;
    const double pivot = tableau[debut].angle;

    if(debut >= fin){
        return medianeAngle(tableau,fin+1);

    }
        

    while(1){

        do droite--; while(tableau[droite].angle > pivot);
        do gauche++; while(tableau[gauche].angle < pivot);

        if(gauche < droite)
            echangerDoublet(tableau, gauche, droite);
        else break;
    }
    quickSortDoubletAngle(tableau, debut, droite);
    quickSortDoubletAngle(tableau, droite+1, fin);
}


void quickSortPoint(POINT tableau[], int debut, int fin){

    int  i;
    int gauche = debut-1;
    int droite = fin+1;
    const double pivot = tableau[debut].x;

    if(debut >= fin){
        for(i=0;i<fin+1;i++){
            if(tableau[i].x==tableau[i+1].x){
                if(tableau[i].y>tableau[i+1].y)
                echangerPoint(tableau,i,i+1);
            }
        }

        return;
    }
        

    while(1){
        //problème au niveau du tri à revoir
        //trié en fonction du y voir open classroom quickSort
        // if(tableau[droite].x==tableau[gauche].x){
        //     if(tableau[droite].y>=tableau[gauche].y){
        //         droite -=1;
        //     }
        //     else{
        //         gauche +=1;
        //     }
        // }
        do droite--; while(tableau[droite].x > pivot);
        do gauche++; while(tableau[gauche].x < pivot);

        if(gauche < droite)
            echangerPoint(tableau, gauche, droite);
        else break;
    }
    quickSortPoint(tableau, debut, droite);
    quickSortPoint(tableau, droite+1, fin);
}

/*Calcul de la valeur médiane d'un tableau*/

double medianeMediatrice(DOUBLET tableau[],int longueur){
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

double medianeAngle(DOUBLET tableau[],int longueur){
    double valeur;
    if (longueur%2 == 0){
        valeur=(((tableau[(longueur/2)-1].angle)+(tableau[(longueur/2)].angle))/2);
        return valeur;
    }
    else{
        valeur=((tableau[((longueur+1)/2)-1].angle));
        return valeur;
    }
}

