#include <stdio.h>


#include "structures.h"
#include "fonctions_fischer.h"


int main()
{

    CERCLE vraiC; //Solution universelle pour les 3 tests
    vraiC.x = 10.0; vraiC.y=10.0; vraiC.d=10.0; 
    int nbPoints;

    // Test 1 : Points cocirculaires

    
    printf("\n** Test 1 : Points cocirculaires **\n\n");

    POINT tab1[] = {{10.0,15.0},{10.0,5.0},{5.0,10.0},{15.0,10.0}}; 
    nbPoints = sizeof(tab1) / sizeof (tab1[0]);

    printf("Tableau donnee: ");
    for(int i=0;i<nbPoints;i++)
        printf("%f %f; ", tab1[i].x, tab1[i].y);
    
    printf("\nLe polygone convexe est:\n");

    polygon P;
    convex_hull(tab1,nbPoints,&P);
    printf("\n");
    print_polygon(&P);


    /*CERCLE c1 = algorithme_fischer(tab1,nbPoints);
    printf("Cercle solution: Coordonnées x=%f, y=%f, diamètre=%lf.\n",c1.x,c1.y,c1.d);
    printf("Le résultat devrait être x=10, y=10, d=10\n");*/

    // Test 2 : Points alignés

    POINT tab2[] = {{10.0,15.0},{10.0,14.0},{10.0,5.0},{10.0,7.0}}; 
    printf("\n** Test 2 : Points alignés **\n\n");
    nbPoints = sizeof(tab2) / sizeof (tab2[0]);
    printf("Tableau donnee: ");
    for(int i=0;i<nbPoints;i++)
        printf("%f %f; ", tab2[i].x, tab2[i].y);
    printf("\n Le determinant donnee par les 3 premiers points devrait etre 0, la fonction donne %f \n",calculer_determinant3(tab2[0],tab2[1],tab2[2]));
    printf("L'enveloppe convexe devrait etre 10 15; 10 5; \n La fonction donne:\n");


    polygon Q;
    convex_hull(tab2,nbPoints,&Q);
    print_polygon(&Q);
    

    //printf("Nombre de points: %d\n",nbPoints);
    /*CERCLE c2 = algorithme_fischer(tab2,nbPoints);
    printf("Cercle solution: Coordonnées x=%f, y=%f, diamètre=%lf.\n",c2.x,c2.y,c2.d);
    printf("Le résultat devrait être x=10, y=10, d=10\n");*/

    // Test 3 : Points confondus

    POINT tab3[] = {{10.0,10.0},{10.0,10.0},{10.0,10.0},{10.0,15.0},{10.0,5.0}};    
    printf("\n** Test 3 : Points confondus **\n\n");
    printf("Tableau initial: ");
    for(int i=0;i<nbPoints;i++)
        printf("%f %f; ", tab3[i].x, tab3[i].y);
    nbPoints = sizeof(tab3) / sizeof (tab3[0]);
    printf("\nNombre de points: %d\n",nbPoints);
    sort_and_remove_duplicates(tab3,&nbPoints);
    printf("Apres le tri: %d points et les elements restants sont: ",nbPoints);
    for(int i=0;i<nbPoints;i++)
        printf("%f %f; ", tab3[i].x, tab3[i].y);
    /*CERCLE c3 = algorithme_fischer(tab3,nbPoints);
    printf("Cercle solution: Coordonnées x=%f, y=%f, diamètre=%lf.\n",c3.x,c3.y,c3.d);
    printf("Le résultat devrait être x=10, y=10, d=10\n");*/



    // Résultat

    /*if ( estEgal(c1, vraiC) && estEgal(c2, vraiC) && estEgal(c3, vraiC) ){
       printf(" \n\n     => Résultat CONFORME! \n"); 
    } else {
       printf(" \n\n     => Résultat NON CONFORME! \n");
    }*/

    return 0;
}