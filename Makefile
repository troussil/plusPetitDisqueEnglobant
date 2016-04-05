#Declaration des variables
CC= gcc
CFLAGS= -Wall

#Commandes

all: Test

Test: resolution_brute.o test_resolution_brute.o fonctions_resolution_brute.o
	$(CC) $(CFLAGS) test_resolution_brute.o fonctions_resolution_brute.o resolution_brute.o -lm -o $@

test_resolution_brute.o: test_resolution_brute.c
	$(CC) -c $(CFLAGS) test_resolution_brute.c -lm -o $@

resolution_brute.o: resolution_brute.c
	$(CC) -c $(CFLAGS) resolution_brute.c -lm -o $@

fonctions_resolution_brute.o: fonctions_resolution_brute.c
	$(CC) -c $(CFLAGS) fonctions_resolution_brute.c -lm -o $@

#Nettoyage

clean: 
	rm *.o Test
