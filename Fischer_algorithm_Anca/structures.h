#ifndef structures_h
#define structures_h

#define coo double	/* coordonates */
#define EPSILON	0.000001	/* a quantity small enough to be zero */
#define MAXPOLY	200	/* maximum number of points in a polygon */

typedef struct model_point{
	coo x;
	coo y;
}POINT;

typedef struct model_cercle{
        coo x;
        coo y;
	double d;
} CERCLE;

typedef struct {
	int n;			/* number of points in polygon */
	POINT p[MAXPOLY];	/* array of points in polygon */
} polygon;

#endif
