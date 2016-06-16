all:	test generateur solveur

fonction_megiddo.o:	fonction_megiddo.c fonction_megiddo.h structure.h 
	gcc -Wall -c -lm fonction_megiddo.c  -o fonction_megiddo.o

utils_table.o:	utils_table.c utils_table.h structure.h
	gcc -Wall -c -lm utils_table.c -o utils_table.o

utils.o:	utils.c utils.h structure.h
	gcc -Wall -c -lm utils.c -o utils.o

generateur:	generateur.c
	gcc -Wall generateur.c -o generateur

solveur:	solveur.c structure.h solveur_megiddo.h fonction_megiddo.o solution_brute_contrainte.o utils.o utils_table.o
	gcc  -Wall solveur.c fonction_megiddo.o solution_brute_contrainte.o utils.o utils_table.o -o solveur -lm
        
        
test:	fonction_megiddo.o utils_table.o utils.o testMegiddo.c
	gcc -Wall fonction_megiddo.o utils_table.o utils.o testMegiddo.c -o test -lm -g

 
solution_brute_contrainte.o:	solution_brute_contrainte.c solution_brute_contrainte.h structure.h utils.o utils_table.o
	gcc -Wall -c solution_brute_contrainte.c utils.o utils_table.o -o solution_brute_contrainte.o -lm -g

clean:
	rm *.o test generateur solveur
	rm *.svg
