#ifndef FONCTIONS_FISCHER_H_
#define FONCTIONS_FISCHER_H_



#include "hashset.h"
#include "structures.h"

double distance(POINT a, POINT* b);

hashset_t hashset_difference(hashset_t S, hashset_t T);

int appartenance_conv(POINT p, hashset_t T);

int appartenance_aff(POINT p, hashset_t T);

void dropping(hashset_t* T);

int walking(POINT*c, hashset_t T);

CERCLE* algorithme_fischer(hashset_t S);

#endif