#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "structures.h"
#include "fonctions_fischer.h"

POINT first_point;		/* first hull POINT pour le calcul de l'enveloppe convexe*/


/****************************** fonctions print **************************************/

void print_point(POINT* p)
{
	printf(" ........ %f %f\n",p->x,p->y);
}

void print_droite(DROITE* d)
{
	printf(" ------ %f %f\n",d->a,d->b);
}

void print_cercle(CERCLE* c)
{
	printf("centre: %f %f, diametre: %f\n",c->x,c->y,c->d);
}

/*************************************************************************************/



/****************************** fonctions geometriques *******************************/

/**
 * calcule la distance entre les points a et b
**/
double distance(POINT a, POINT b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double signed_triangle_area(POINT a, POINT b, POINT c)
{
	return( (a.x*b.y - a.y*b.x + a.y*c.x 
		- a.x*c.y + b.x*c.y - c.x*b.y) / 2.0 );
}


/**
 * verifie si a,b,c alignes
**/
int collinear(POINT a, POINT b, POINT c)
{
	double signed_triangle_area();

	return (fabs(signed_triangle_area(a,b,c)) <= EPSILON);
}

/**
 * Teste si les points du tableau sont alignes
 * retourne 1 si oui, 0 sinon
**/
int tableau_collinear(POINT T[], int nbPoints){
	POINT a = T[0];
	POINT b = T[1];
	int i=2;
	
	while(i<nbPoints){
		if(!collinear(a,b,T[i]))
			return 0;
		i++;
	}
	
	return 1;
}


/**
 * Teste si deux cercles c1 et c2 sont égaux
**/
int estEgalCercle( CERCLE c1, CERCLE c2 ){
    if( (c1.x == c2.x) && (c1.y == c2.y) && (c1.d == c2.d) )
        return 1;
    else
        return 0;
}

/**
 * Teste si deux points p1 et p2 sont égaux
**/
int estEgalPoint( POINT p1, POINT p2 ){
    if( (p1.x == p2.x) && (p1.y == p2.y) )
        return 1;
    else
        return 0;
}

/*
 * verifie si le point p == {0,0}
 */
int equals_zero(POINT p){

	if(p.x != 0.0 || p.y != 0.0){
		
		return (0);
	}
	else{
		return (1);
	}
}


/**
 * calcule le determinant (avec la regle du Sarrus):
 * | a.x  b.x  c.x |
 * | a.y  b.y  c.y |
 * |  1    1    1  |
 *
**/
double calculer_determinant3(POINT a, POINT b, POINT c){
	return a.x*b.y + a.y*c.x + b.x*c.y - b.y*c.x - a.y*b.x - a.x*c.y;
}

/**
 * calcule le determinant:
 * | a.x  b.x |
 * | a.y  b.y |
 *
**/
double calculer_determinant2(POINT a, POINT b){
	return a.x*b.y - a.y*b.x;
}

//retourne l'index d'un POINT avec des coeffs negatifs dans l'ecriture p = alpha*T[i] + betha*T[j]
//on utilise Cramer pour un systeme de dimension 2
int coefficients_negatifs(POINT p,POINT T[], int nbPoints){
	double alpha;
	double betha;
	int i,j;

	for(i=0; i<nbPoints-1;i++){
		for(j=i+1;j<nbPoints;j++){
			if(calculer_determinant2(T[i],T[j])!=0){

				alpha=calculer_determinant2(p,T[j])/calculer_determinant2(T[i],T[j]);
				//printf("alpha = %lf", alpha);

				if(alpha<=0){
					return i;
				}
				else{
					betha=calculer_determinant2(T[i],p)/calculer_determinant2(T[i],T[j]);
					//printf("betha = %lf", betha);
					if(betha<=0) 
						return j;
				}
			}
		}
	}
	return -1;
}

/*
 * retourne 1 si p appartient a conv(T), 0 sinon
 *
 */
int appartenance_conv(POINT p,POINT T[], int nbPoints)
{
	
    if(nbPoints == 1)
    {
    	//si on a 1 seul point, les points doivent etre confondus
    	if(distance(p,T[0])<=EPSILON)
    		return 1;
    	else
    		return 0;
    } 
    else if(nbPoints==2)
    {
    	//si on a 2 points dans T, p doit etre sur le segment qu'elles determinent
    	//les 3 points doivent etre donc colineailres et le produit scalaire pT[0] , pT[1] doit etre negatif ou nul
    	if( collinear(T[0],T[1],p) && (((T[0].x - p.x)*(T[1].x - p.x) + (T[0].y - p.y)*(T[1].y - p.y)) <= 0 ))
    		return 1;
    	else
    		return 0;
    }
    else
    {
    	POINT tab01[2];
    	tab01[0] = T[0];
    	tab01[1] = T[1];

    	POINT tab02[2];
    	tab02[0] = T[0];
    	tab02[1] = T[2];

    	POINT tab12[2];
    	tab12[0] = T[1];
    	tab12[1] = T[2];

    	if(!tableau_collinear(T,nbPoints)){

	    	//sinon on a 3 points non colineaires, et donc p doit etre dans un triangle
	    	//si pour chaque segment du triangle p et l'autre point sont de meme cote ou si p est sur le segment, alors p est dans le triangle

	    	if(calculer_determinant3(T[0],T[1],p)*calculer_determinant3(T[0],T[1],T[2]) > 0 || appartenance_conv(p,tab01,2))
	    		if(calculer_determinant3(T[0],T[2],p)*calculer_determinant3(T[0],T[2],T[1]) > 0 || appartenance_conv(p,tab02,2))
	    			if(calculer_determinant3(T[2],T[1],p)*calculer_determinant3(T[2],T[1],T[0]) > 0 || appartenance_conv(p,tab12,2))
	    				return 1;
	    			else
	    				return 0;
	    		else 
	    			return 0;
	    	else
	    		return 0;
	    }
	    else{
	    	//si les points sont collineaires, il faut que p soit aussi sur la droite et il faut appartenir a un segment determine par 2 points
	    	return(collinear(T[0],T[1],p) && ( appartenance_conv(p,tab01,2) || appartenance_conv(p,tab02,2) || appartenance_conv(p,tab12,2) ));
	    }
    }
}


/*
 *retourne 1 si p appartient a aff(T), 0 sinon
 */
int appartenance_aff(POINT p,POINT T[], int nbPoints){

	//si on a un seul point, il faut que p et T[0] coincident pour que p appartienne a aff(T)
	if(nbPoints==1 && distance(p,T[0])!=0)
	{
		return 0; //distance != 0 => points differents => p appartient pas a aff(T)
	} 
	else if(nbPoints==1 && distance(p,T[0]) ==0)
	{
		return 1; //distance == 0 => points coincident => p appartient a aff(T)
	}
	else if(tableau_collinear(T,nbPoints))
	{
		//si les POINT de T sont allignes, il faut que p appartienne a la droite pour qu'il appartienne a aff(T)
		//on peut considerer ici le cas ou dans T il y a que 2 points aussi
		return collinear(p,T[0],T[1]);
	}
	else{ 
		//si les points ne sont pas allignes, l'espace affine c'est tout le plan et donc p y appartienne
		return 1;
	}
}

/*
 * Renvoie le cercle le plus petit passant par deux points p1 et p2
 */
CERCLE cerclePassantParDeuxPoints( POINT p1 , POINT p2){
	
	CERCLE c;
		
	c.x = (p1.x + p2.x)/2;
	c.y = (p1.y + p2.y)/2;
	c.d = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	
	return c;	
}


/*
 * Renvoie le cercle le plus petit passant par trois points p1, p2 et p3
 */
CERCLE cerclePassantParTroisPoints( POINT p1 , POINT p2 , POINT p3){
	
	CERCLE c;
	double det =  (p1.x - p2.x) * (p2.y - p3.y) - (p2.x - p3.x)* (p1.y - p2.y); 

    	if (det == 0) { 
    	
    	c = cerclePassantParDeuxPoints(p1,p2);

    	if(c.d < (cerclePassantParDeuxPoints(p3,p2).d))
    		c = cerclePassantParDeuxPoints(p3,p2);
    	else if(c.d < (cerclePassantParDeuxPoints(p3,p1).d))
    		c = cerclePassantParDeuxPoints(p3,p1);

	} else {
		int offset = pow(p2.x,2) + pow(p2.y,2);
    		int bc =   ( pow(p1.x,2) + pow(p1.y,2) - offset )/2.0;
    		int cd =   (offset - pow(p3.x, 2) - pow(p3.y, 2))/2.0;

	    	c.x =  (bc * (p2.y - p3.y) - cd * (p1.y - p2.y)) / det;
	    	c.y =  (cd * (p1.x - p2.x) - bc * (p2.x - p3.x)) / det;
	    	c.d = 2 * sqrt( pow(p2.x - c.x,2) + pow(p2.y-c.y,2));
	}
	return c;	
}

DROITE mediatrice(POINT p1, POINT p2)
{
	DROITE res;
	res.a = (-1.0)/ ((p1.y - p2.y)/(p1.x - p2.x));
	res.b = ((p1.y + p2.y)/2.0) - res.a * ((p1.x + p2.x)/2.0);
	return res;
}

POINT intersection(DROITE d1, DROITE d2)
{
	POINT res;
	res.x = (d1.b - d2.b)/(d2.a - d1.a);
	res.y = d1.a * res.x + d1.b;
	return res;
}

DROITE droitePassantParPoints(POINT p1, POINT p2)
{
	DROITE res;
	res.a = (p1.y - p2.y)/(p1.x - p2.x);
	res.b = p1.y - res.a * p1.x ;
	return res;
}


/**************************** fonctions pour les tableaux ****************************/

/**
 * tri des points et enlevement des dupliques
**/
void sort_and_remove_duplicates(POINT in[], int *n)
{
    int i;                  /* counter */
    int oldn;               /* number of points before deletion */
    int hole;               /* index marked for potential deletion */
	int leftlower();

	qsort(in, *n, sizeof(POINT), leftlower);

    oldn = *n;
	hole = 1;
        for (i=1; i<oldn; i++) {
		if ((in[hole-1].x == in[i].x) && (in[hole-1].y == in[i].y)) 
            (*n)--;
        else {
            in[hole].x = in[i].x;
            in[hole].y = in[i].y;
            hole = hole + 1;
        }
    }
    in[hole].x = in[oldn-1].x;
    in[hole].y = in[oldn-1].y;
}



//pour le tri
int leftlower(POINT *p1, POINT *p2)
{
	if ((*p1).x < (*p2).x) return (-1);
	if ((*p1).x > (*p2).x) return (1);

    if ((*p1).y < (*p2).y) return (-1);
    if ((*p1).y > (*p2).y) return (1);

	return(0);
}


/*
 * initialisation tableau avec {0,0} partout
 */
void init_tab(POINT tab[], int nbPoints){
	int i;
	for(i=0;i<nbPoints;i++){
		tab[i].x=0;
		tab[i].y=0;
	}
}

/*
 * verifie si le POINT element se trouve dans le tableau tab
 * retourne 0 si on trouve l'element dans le tableau, 1 sinon
 */
int not_in(POINT tab[], POINT element, int nbPoints){
	int i;
	for(i=0;i<nbPoints;i++)
		if(estEgalPoint(tab[i], element))
			return 0;
	return 1;
}



/**************************** fonctions specifiques a l'algo *************************/




/*
 *on efface du tableau T un element qui a des coeffs negatifs dans la decomposition c = coeff[i]*T[i]
 */
int dropping(POINT c,POINT T[], int nbPoints){

	int i;
	int index = coefficients_negatifs(c, T, nbPoints);
	if(index == -1){
		printf("erreur: pas des coeffs negatifs pour le dropping");
		return 0;
	}
	for(i=index;i<nbPoints-1;i++)
		T[i]=T[i+1];
	T[nbPoints-1].x = 0;
	T[nbPoints-1].y = 0;
	return 1;
}


/*
 * prend en paramentre le set S et renvoie le cercle minimal contenant S
 */
CERCLE algorithme_fischer(POINT S[], int nbPoints){

	CERCLE resultat;

	CERCLE temp; //un cercle temporaire 
	POINT centreTemp;
	double diametreTemp;
	POINT c,r,p,q;

	POINT T[3];
	POINT S2[nbPoints-2]; //l'ensemble des points de S qui se trouvent du bon côté de la droite passant par les deux points de T

	double det; //pour stocker la valeur du determinant
	double max=0;
	int i,j,nbPointsT,nbPointsS2;

	sort_and_remove_duplicates(S,&nbPoints); //on enleve les points dupliques de S pour faire moins de calculs et eviter les ambiguites

	//les iterations sont faites pour les paires c,T
	//c est le centre du cercle courant et T le set des points support

	if(tableau_collinear(S,nbPoints))
	{
		resultat = cerclePassantParDeuxPoints(S[0],S[nbPoints-1]);
	}
	else
	{
			c = S[0]; //au debut, c est pris au hasard
			
			for(i=1; i<nbPoints;i++)
		    {
		    	q = S[i];
		    	if(max < distance(c,q)){
		    		max = distance(c,q);
		    		p = q;
		    	}
		    }

			init_tab(T,3);
			T[0] = p; //au debut, T contient p seulement
			nbPointsT = 1;

			int compteur = 0;

			while(!appartenance_conv(c,T,nbPointsT)){


				compteur++;
				
				printf("\n*** iteration %d ***\n\n", compteur);
				printf("c.x = %f c.y = %f\n",c.x,c.y);
				printf("Dans T on a %d points : \n", nbPointsT);
				for(i=0;i<nbPointsT;i++){
					printf("%f %f\n", T[i].x, T[i].y);
				}

								
				if(nbPointsT>=3 || appartenance_aff(c,T,nbPointsT) )
				{
					//on a 3 points ou plus dans T, faut enlever un par le dropping
					
					if(dropping(c,T,nbPointsT)){
						nbPointsT--;
					}
					else{
						//ajouter point T ??

					}
				}
				else if(nbPointsT == 1)
				{
					
					//on a 1 seul point, faut rajouter encore 1 point dans T
					
					//calcul du tableau S2 = S\T
					init_tab(S2, nbPoints-1);
					j=0;

					for(i=0;i<nbPoints;i++){
						if(not_in(T,S[i],nbPointsT)){
							S2[j] = S[i];
							j++;
						}
					}
					nbPointsS2=j;

					q = S2[0];

					r.x =0;
					r.y =0;
					
					for(i=1;i<nbPointsS2;i++){
						DROITE d1 = mediatrice(T[0],q);
						DROITE d2 = droitePassantParPoints(T[0],c);

						centreTemp = intersection(d1,d2);
						diametreTemp = 2 * distance(centreTemp, q);

						temp.x = centreTemp.x;
						temp.y = centreTemp.y;
						temp.d = diametreTemp;

						if(!contientPoint(temp, S2[i])){
							r = S2[i];
							c = centreTemp;
						}

					}

					if(!equals_zero(r)){
						T[1] = r;
						nbPointsT++;
					}
					else{
						//printf("nous n'avons pas pu rajouter un 2eme point car r.x = %f et r.y = %f", r.x, r.y);
						T[1] = c;
						nbPointsT++;
						c.x = (T[0].x + T[1].x)/2.0;
						c.y = (T[0].y + T[1].y)/2.0;
					}
				}
				else if(nbPointsT==2) 
				{
					// Calcul du tableau S2 (les points de S/T du meme cote que c)
					// le calcul est fait seulement dans le cas ou on a 2 points dans T

					j=0; // compteur pour S2
					det = calculer_determinant3(T[0],T[1],c);
					init_tab(S2, nbPoints-1);
					for(i=0;i<nbPoints;i++){
						if(not_in(T,S[i],nbPointsT))
						{
							if(det * calculer_determinant3(T[0],T[1],S[i]) > 0)
							{
								S2[j] = S[i];
								j++;
							}
						}
					}
					nbPointsS2 = j;

					if(nbPointsS2!=0){

						//calcul du cercle temp passant par les 2 points de T et 1 point de S2 
						temp = cerclePassantParTroisPoints(T[0], T[1], S2[0]);
						centreTemp.x = temp.x;
						centreTemp.y = temp.y;
						

						T[2] = S2[0]; //le point sur le bord du cercle est rajoute a T
						
						for(i=1;i<nbPointsS2;i++){
							//si S2[i] est en dehors du cercle temp, on reactualise le cercle
							if(!contientPoint(temp,S2[i])){
								//temp devient le cercle passant par T[0], T[1], S2[i]
								temp = cerclePassantParTroisPoints(T[0], T[1], S2[i]);
								centreTemp.x = temp.x;
								centreTemp.y = temp.y;
								T[2] = S2[i]; //le point sur le bord du cercle est rajoute a T
							}
						}
						nbPointsT++;

						//on reactualise le centre c

						DROITE d1 = mediatrice(T[0],T[1]);
						DROITE d2 = mediatrice(T[0],T[2]);
						c = intersection(d1,d2);
					}
					else
					{
						if(!not_in(S,c,nbPoints)){
							T[2]=c;
							nbPointsT++;
						} 
						c.x = (T[0].x + T[1].x)/2;
						c.y = (T[0].y + T[1].y)/2;


					}

				}
				//sleep(5);	
			}
		    //on renvoye le cercle resultat de centre c et diametre 2 * distance (c,T[0])
			resultat.x = c.x;
			resultat.y = c.y;
			resultat.d = 2*distance(c,T[0]);

	printf("\non a fait %d iterations \n",compteur);			
	}
	return resultat;
}




/**************************** fonctions resolution brute *************************/

//Renvoie 1 si tous les point du tableau tab sont contenus dans le cercle c

int contientTousPoint( CERCLE c , POINT tab[] , int nbPoints ){
	
	int i = 0;	
	int ok = 1;
	
	while(i<nbPoints && ok) {

		if (!contientPoint( c, tab[i] ))
		{
			ok = 0;
		}

	   	i++;
	}
	
	return ok;
}

int contientPoint( CERCLE c , POINT p){

	if(c.x + c.d/2 < p.x + EPSILON || c.x - c.d/2 > p.x - EPSILON || c.y + c.d/2 < p.y + EPSILON || c.y - c.d/2 > p.y - EPSILON)
		return 0;
	else
		return 1;

}

/**
 * @param tab Tableau contenant les points
 * @return cFinal CERCLE solution finale
**/
CERCLE brute( POINT tab[] , int nbPoints ){

	CERCLE cFinal , cTemp;
	cFinal.d = 100000000000; cFinal.x = 0; cFinal.y=0;	

	POINT p1 , p2 , p3;
	
	int i , j , k;
	int compteur = 0;

	if(nbPoints == 1){
		cFinal.x = tab[0].x;
		cFinal.y = tab[0].y;
		cFinal.d = 0;
	}
	else
	{
		/* TESTS AVEC DUO DE POINTS */
	
		for(i=0 ; i<nbPoints ; i++){
			for(j=i+1 ; j<nbPoints ; j++){
				compteur ++;
				p1 = tab[i];
				p2 = tab[j];
				cTemp = cerclePassantParDeuxPoints(p1 , p2);
				if ( contientTousPoint(cTemp , tab , nbPoints) && cTemp.d < cFinal.d){
					cFinal = cTemp;
				}
			}
		}
	
		/* TESTS AVEC TRIO DE POINTS */   
	
		for(i=0 ; i<nbPoints ; i++){
	        for(j=0 ; j<nbPoints ; j++){
	            for(k=0 ; k<nbPoints ; k++){
	            	compteur ++;
					if(i!=j && i!=k && j!=k){
	                	p1 = tab[i];
	                	p2 = tab[j];
						p3 = tab[k];
	        	        cTemp = cerclePassantParTroisPoints(p1 , p2 , p3);
	              	  	if ( contientTousPoint(cTemp , tab , nbPoints) && cTemp.d < cFinal.d){
	                	        cFinal = cTemp;
	                	}
					}
	            }
	        }
	    }
	    printf("\non a fait %d iterations \n",compteur);
	}


	return cFinal;
}