#include <stdio.h>

#include "hashset.h"

#include "structures.h"

int main()
{   POINT p1 = {10,15};
    POINT p2 = {10,5};
    POINT p3 = {5,10};
    POINT p4 = {15,10};
    POINT p5 = {0,0};
    POINT *items[] = {&p1,&p2,&p3,&p4,NULL}; 
    size_t ii, nitems = 4;
    hashset_t set = hashset_create();

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
    

    return 0;
}