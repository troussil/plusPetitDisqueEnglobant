#Declaration des variables
CC= gcc
CFLAGS= -Wall

#Commandes

all: Test

Test: resolution_brute.o test_resolution_brute.o fonctions_resolution_brute.o generateur.o solveur.o
	$(CC) $(CFLAGS) test_resolution_brute.o fonctions_resolution_brute.o resolution_brute.o generateur.o solveur.o -lm -o $@

test_resolution_brute.o: test_resolution_brute.c
	$(CC) -c $(CFLAGS) test_resolution_brute.c -lm -o $@

resolution_brute.o: resolution_brute.c
	$(CC) -c $(CFLAGS) resolution_brute.c -lm -o $@

fonctions_resolution_brute.o: fonctions_resolution_brute.c
	$(CC) -c $(CFLAGS) fonctions_resolution_brute.c -lm -o $@

generateur.o: generateur.c
	$(CC) -c $(CFLAGS) generateur.c -lm -o $@

generateur: generateur.o
	$(CC) $(CFLAGS) generateur.o -lm -o $@

solveur.o: solveur.c
	$(CC) -c $(CFLAGS) solveur.c -lm -o $@

solveur: solveur.o
	$(CC) $(CFLAGS) solveur.o -lm -o $@


#Nettoyage

clean: 
	rm *.o Test
