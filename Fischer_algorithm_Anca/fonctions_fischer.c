#include <stdio.h>

#include "hashset.h"
#include "hashset_itr.h"
#include "structures.h"

int appartenance_conv(POINT p, hashset_t T){
	//retourne 1 si p appartient a conv(T), 0 sinon
	//TODO
}

int appartenance_aff(POINT p, hashset_t T){
	//retourne 1 si p appartient a aff(T), 0 sinon
	//TODO
}

void dropping(hashset_t* T){
	//TODO trouver le point q qu'on doit enlever
	//hashset_remove(T, &q)
}

int walking(POINT*c, hashset_t T){
	//TODO deplace c vers cc(T)
}

CERCLE algorithme_fischer(hashset_t S){
	POINT c, p; // a initialiser c=point random, p=le plus loin point de c
	hashset_t T = hashset_create();
	hashset_add(T, &p);
	while(!appartenance_conv(c,T)){
		if(appartenance_aff(c,T)){
			dropping(&T);
			walking(&c, T);
		}
	}
	CERCLE resultat;
	resultat.x = c.x;
	resultat.y = c.y;
	// resultat.d = 2*distance entre c et un point de T
	return resultat;
}
