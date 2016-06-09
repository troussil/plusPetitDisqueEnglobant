#Declaration des variables
CC= gcc
CFLAGS= -Wall

#Commandes

all: generateur solveur test_resolution_brute 

###

generateur: generateur.c
	$(CC) $(CFLAGS) $< -o $@

solveur: solveur.c fonctions_resolution_brute.o resolution_brute.o  
	$(CC) $(CFLAGS) $^ -lm -o $@

test_resolution_brute: resolution_brute.o test_resolution_brute.o fonctions_resolution_brute.o
	$(CC) $(CFLAGS) $^ -lm -o $@

###

test_resolution_brute.o: test_resolution_brute.c
	$(CC) -c $(CFLAGS) $< -lm -o $@

resolution_brute.o: resolution_brute.c
	$(CC) -c $(CFLAGS) resolution_brute.c -lm -o $@

fonctions_resolution_brute.o: fonctions_resolution_brute.c
	$(CC) -c $(CFLAGS) fonctions_resolution_brute.c -lm -o $@


#Nettoyage
clean: 
	rm -f *.o
	rm -f *.svg
	rm -f *~
	rm generateur solveur test_resolution_brute 
