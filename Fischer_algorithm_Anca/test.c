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

    CERCLE c1 = brute(tab , N);

    printf("Time ellapsed: %lf\n", (double) (clock() - now) / CLOCKS_PER_SEC);
    printf("Centre ( %lf , %lf ) diamètre %lf\n", c1.x , c1.y , c1.d );

    

    printf("\n*** Algorithme Fischer *** \n\n");   

    now=0;
    CERCLE c2 = algorithme_fischer(tab , N);

    printf("Time ellapsed: %lf\n", (double) (clock() - now) / CLOCKS_PER_SEC);
    printf("Centre ( %lf , %lf ) diamètre %lf\n\n", c2.x , c2.y , c2.d );

    //printf("contientTousPoints donne: %d \n", contientTousPoint( c2 , tab , N ));

    return 0;
}