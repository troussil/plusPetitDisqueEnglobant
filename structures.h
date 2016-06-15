#include <math.h>
#ifndef structures_h
#define structures_h

#define coo double

typedef struct model_point{
	coo x;
	coo y;
        coo norme;
} POINT;

typedef struct model_cercle{
        coo x;
        coo y;
	coo d;
} CERCLE;


#endif

