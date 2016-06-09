#ifndef structures_h
#define structures_h

#define coo double

typedef struct model_point{
	coo x;
	coo y;
} POINT;


typedef struct model_cercle{
        coo x;
        coo y;
	double d;
} CERCLE;


/**
 * Une structure permettant de retourner un tableau de points et la taille qu'il fait
 * (utilisé pour la méthode prune)
**/ 

typedef struct tabOfPoints_and_size{
    POINT* tab;
	int nbPoints;
} POINTS_AND_NB;

/**
 * Une structure permettant de retourner un tableau de points, la taille qu'il fait, le point le plus loin, et une distance
 * (utilisé pour la méthode farthPtPrune)
**/ 

typedef struct tabOfPoints_and_size_and_point_and_dist{
    POINT* tab;
	int nbPoints;
	POINT farthest;
	double distance;
} POINTS_AND_SPD;


/**
 * Une structure permettant de retourner un centre et un rayon
 * (utilisé pour la méthode initializeBall et updateBall)
**/ 

typedef struct point_and_dist{
    POINT center;
	double radius;
} POINT_AND_R;




#endif
