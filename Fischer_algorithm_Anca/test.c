#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "fonctions_fischer.h"


int rand_a_b (int a, int b){
    int res = rand()%(b-a )+a; 
    return res;
}

int main( int argc, char* argv []){

    /****************************** Tests unitaires **************************************/

    /*
    POINT a;
    POINT b;
    POINT c;

    POINT p;
    POINT q;

    double x,y;

    int i;

    printf("\nVeuilles rentrer les coordonnes du point a:");

    scanf("%lf", &x);
    scanf("%lf", &y);
    a.x = x;
    a.y = y;
    printf("\nPoint a = %lf %lf\n", a.x, a.y);

    printf("\nVeuilles rentrer les coordonnes du point b:");

    scanf("%lf", &x);
    scanf("%lf", &y);
    b.x = x;
    b.y = y;
    printf("\nPoint b = %lf %lf\n", b.x, b.y);

    printf("\nVeuilles rentrer les coordonnes du point c:");

    scanf("%lf", &x);
    scanf("%lf", &y);
    c.x = x;
    c.y = y;
    printf("\nPoint c = %lf %lf\n", c.x, c.y);              

    printf("\ndistance ab = %lf et ba = %lf\n", distance(a,b), distance(b,a));
    printf("distance aa = %lf\n", distance(a,a));

    printf("\ndeterminant a,b,c avec la methode calculer_determinant3: %lf\n", calculer_determinant3(a,b,c));

    p.x = a.x - c.x;
    p.y = a.y - c.y;

    q.x = b.x - c.x;
    q.y = b.y - c.y;

    printf("determinant a,b,c par reduction avec calculer_determinant2: %lf\n", calculer_determinant2(p,q));


    POINT tab[]={a,b,c};
    int nbPoints = (int)(sizeof(tab)/sizeof(POINT));
    printf("\nMaintenant on teste le dropping. Veullez rentrer encore un point p: ");
    scanf("%lf", &x);
    scanf("%lf", &y);
    p.x = x;
    p.y = y;
    printf("\nPoint p = %lf %lf\n", p.x, p.y);
    printf("\nappartennance_aff de p dans {a,b,c} donne: %lf\n",appartenance_aff(p,tab,nbPoints));
    printf("\nappartennance_conv de p dans {a,b,c} donne: %lf\n",appartenance_conv(p,tab,nbPoints));

    int index = coefficients_negatifs(p, tab, nbPoints);

    if(index==0)
        printf("\nla methde coefficients_negatifs indique d'eliminer le point a\n");
    else if(index==2)
        printf("\nla methde coefficients_negatifs indique d'eliminer le point b\n");
    else if(index==3)
        printf("\nla methde coefficients_negatifs indique d'eliminer le point c\n");
    else
        printf("\non ne peut eliminer aucun point %lf\n",index);

    dropping(p,tab,nbPoints);

    printf("\n apres le dropping il nous reste:\n");
    for(i=0;i<nbPoints;i++)
        print_point(&tab[i]);

  */  


    /****************************** Tests et comparaison algorithme **************************************/


    int N, xmin , xmax, ymin, ymax;

    if (argc!=6 || atoi(argv[1])>500000){ //Plus de 600 000 points provoquent une segmentation fault
        printf("usage: %s <nbDePoints (inf. à 500000)> <xmin> <xmax> <ymin> <ymax> \n\n", argv[0]); 
        return 0;
    }

    N=atoi(argv[1]);
    
    POINT tab[N];


    xmin=atoi(argv[2]);   
    xmax=atoi(argv[3]);
    ymin=atoi(argv[4]);
    ymax=atoi(argv[5]);



    int i=0;

    for (i=0;i<N;i++){
        tab[i].x =rand_a_b(xmin,xmax);
        tab[i].y =rand_a_b(ymin,ymax);
    }

    

    clock_t now;
    now=0;


    printf("\n*** Algorithme brut *** \n\n");

    CERCLE c0 = brute(tab , N);

    printf("Time ellapsed: %lf\n", (double) (clock() - now) / CLOCKS_PER_SEC);
    printf("Centre ( %lf , %lf ) diamètre %lf\n", c0.x , c0.y , c0.d );
    printf("contientTousPoints donne: %d\n", contientTousPoint(c0,tab,N));
    

    POINT tab1[] = {{10.0,15.0},{10.0,5.0},{5.0,10.0},{15.0,10.0}}; 
    printf("\n** Test 1 : Points cocirculaires **\n\n");
    int nbPoints = sizeof(tab1) / sizeof (tab1[0]);
    //printf("Nombre de points: %lf\n",nbPoints);
    CERCLE c1 = algorithme_fischer(tab1,nbPoints);
    printf("Cercle solution brute: Coordonnées x=%lf, y=%lf, diamètre=%lf.\n",c1.x,c1.y,c1.d);
    printf("Le résultat devrait être x=10, y=10, d=10\n");

    // Test 2 : Points alignés

    POINT tab2[] = {{10.0,15.0},{10.0,14.0},{10.0,5.0},{10.0,7.0}}; 
    printf("\n** Test 2 : Points alignés **\n\n");
    nbPoints = sizeof(tab2) / sizeof (tab2[0]);
    //printf("Nombre de points: %lf\n",nbPoints);
    CERCLE c2 = algorithme_fischer(tab2,nbPoints);
    printf("Cercle solution brute: Coordonnées x=%lf, y=%lf, diamètre=%lf.\n",c2.x,c2.y,c2.d);
    printf("Le résultat devrait être x=10, y=10, d=10\n");

    // Test 3 : Points confondus

    POINT tab3[] = {{10.0,10.0},{10.0,10.0},{10.0,10.0},{10.0,15.0},{10.0,5.0}};    
    printf("\n** Test 3 : Points confondus **\n\n");
    nbPoints = sizeof(tab3) / sizeof (tab3[0]);
    //printf("Nombre de points: %lf\n",nbPoints);
    CERCLE c3 = algorithme_fischer(tab3,nbPoints);
    printf("Cercle solution brute: Coordonnées x=%lf, y=%lf, diamètre=%lf.\n",c3.x,c3.y,c3.d);
    printf("Le résultat devrait être x=10, y=10, d=10\n");

    

    printf("\n*** Algorithme Fischer *** \n\n");   

    now=0;
    CERCLE c4 = algorithme_fischer(tab , N);

    printf("Time ellapsed: %lf\n", (double) (clock() - now) / CLOCKS_PER_SEC);
    printf("Centre ( %lf , %lf ) diamètre %lf\n\n", c4.x , c4.y , c4.d );
    printf("contientTousPoints donne: %d\n", contientTousPoint(c4,tab,N));



    return 0;
}