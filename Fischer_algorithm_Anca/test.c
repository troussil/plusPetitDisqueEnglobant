#include <stdio.h>


#include "structures.h"
#include "fonctions_fischer.h"


int main()
{

    CERCLE vraiC; //Solution universelle pour les 3 tests
    vraiC.x = 10.0; vraiC.y=10.0; vraiC.d=10.0; 

    // Test 1 : Points cocirculaires

    POINT tab1[] = {{10.0,15.0},{10.0,5.0},{5.0,10.0},{15.0,10.0}}; 
    printf("\n** Test 1 : Points cocirculaires **\n\n");
    int nbPoints = sizeof(tab1) / sizeof (tab1[0]);
    printf("Nombre de points: %d\n",nbPoints);
    CERCLE c1 = algorithme_fischer(tab1,nbPoints);
    printf("Cercle solution: Coordonnées x=%f, y=%f, diamètre=%lf.\n",c1.x,c1.y,c1.d);
    printf("Le résultat devrait être x=10, y=10, d=10\n");

    // Test 2 : Points alignés

    POINT tab2[] = {{10.0,15.0},{10.0,14.0},{10.0,5.0},{10.0,7.0}}; 
    printf("\n** Test 2 : Points alignés **\n\n");
    nbPoints = sizeof(tab2) / sizeof (tab2[0]);
    printf("Nombre de points: %d\n",nbPoints);
    CERCLE c2 = algorithme_fischer(tab2,nbPoints);
    printf("Cercle solution: Coordonnées x=%f, y=%f, diamètre=%lf.\n",c2.x,c2.y,c2.d);
    printf("Le résultat devrait être x=10, y=10, d=10\n");

    // Test 3 : Points confondus

    POINT tab3[] = {{10.0,10.0},{10.0,10.0},{10.0,10.0},{10.0,15.0},{10.0,5.0}};    
    printf("\n** Test 3 : Points confondus **\n\n");
    nbPoints = sizeof(tab3) / sizeof (tab3[0]);
    printf("Nombre de points: %d\n",nbPoints);
    CERCLE c3 = algorithme_fischer(tab3,nbPoints);
    printf("Cercle solution: Coordonnées x=%f, y=%f, diamètre=%lf.\n",c3.x,c3.y,c3.d);
    printf("Le résultat devrait être x=10, y=10, d=10\n");


    POINT in[MAXPOLY];      /* input points */
    polygon hull;           /* convex hull */
    int n;              /* number of points */
    int i;              /* counter */

    scanf("%d",&n);
    for (i=0; i<n; i++)
        scanf("%lf %lf",&in[i].x,&in[i].y);

    convex_hull(in,n,&hull);

    print_polygon(&hull);

    // Résultat

    /*if ( estEgal(c1, vraiC) && estEgal(c2, vraiC) && estEgal(c3, vraiC) ){
       printf(" \n\n     => Résultat CONFORME! \n\n");
       return 0;  
    } else {
       printf(" \n\n     => Résultat NON CONFORME! \n\n");
       return 1; 
    }*/

    return 0;
}