#ifndef structure_h
#define structure_h



#define coo double
#define NB_POINTS 12
//#define coo float


typedef struct model_point{
	coo x;
	coo y;
} POINT;


typedef struct model_cercle{
    coo x;
    coo y;
	double d;
} CERCLE;

typedef struct model_droite{
	double m;
	double p;
} DROITE;

typedef struct model_doublet{
	POINT a;
	POINT b;
	DROITE droite;
	double mediatrice;
	double angle;
} DOUBLET;


#endif
