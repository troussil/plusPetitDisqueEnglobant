#include <stdio.h>

#include "hashset.h"
#include "hashset_itr.h"
#include "structures.h"
#include "fonctions_fischer.h"

int main()
{
    //test creation set points 
    printf("Test creation set points: \n");

    POINT p1 = {10,15};
    POINT p2 = {10,5};
    POINT p3 = {5,10};
    POINT p4 = {15,10};
    POINT p5 = {0,0};
    POINT *items[] = {&p1,&p2,&p3,&p4,NULL}; 
    size_t ii, nitems = 4;
    hashset_t set = hashset_create();
    hashset_itr_t iter = hashset_iterator(set);

    if (set == NULL) {
        fprintf(stderr, "failed to create hashset instance\n");
        abort();
    }

    for (ii = 0; ii < nitems; ++ii) {
        hashset_add(set, items[ii]);
    }

    for (ii = 0; ii < nitems; ++ii) {
        printf("%d\n",hashset_is_member(set, items[ii]));
    }

    printf("%d\n",hashset_is_member(set,&p5));
    
    printf("Le set contient %d points\n", (int)set->nitems);
    
    //test iterateur set points
    printf("Test iterateur set points: \n");

    while(hashset_iterator_has_next(iter))
    {
        
        printf("%d %d\n",((POINT*)hashset_iterator_value(iter))->x, ((POINT*)hashset_iterator_value(iter))->y);
        hashset_iterator_next(iter);
    }
    
    //test algorithme
    CERCLE* seb = algorithme_fischer(set);
    
    printf("resultat: le cercle de centre {%d,%d} et rayon %f\n", seb->x, seb->y, seb->d);

    return 0;
}