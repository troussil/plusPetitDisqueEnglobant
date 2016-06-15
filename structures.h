#ifndef structures_h
#define structures_h

#define coo int

typedef struct model_point{
	coo x;
	coo y;
} POINT;


typedef struct model_cercle{
  coo vide; // si cercle vide, vide=1
  coo x;
  coo y;
	double d;
} CERCLE;


#endif
