all:	test generateur demo

fonction_megiddo.o:	fonction_megiddo.c fonction_megiddo.h structure.h utils.o
	gcc -Wall -c -lm fonction_megiddo.c utils.o -o fonction_megiddo.o

utils_table.o:	utils_table.c utils_table.h structure.h
	gcc -Wall -c -lm utils_table.c -o utils_table.o

utils.o:	utils.c utils.h structure.h
	gcc -Wall -c -lm utils.c -o utils.o

generateur:	generateur.c
	gcc -Wall generateur.c -o generateur

solveur.o:	solveur.c structure.h solveur_megiddo.h
	gcc -c -Wall solveur.c -o solveur.o
        
        
test:	fonction_megiddo.o utils_table.o utils.o testMegiddo.c
	gcc -Wall fonction_megiddo.o utils_table.o utils.o testMegiddo.c -o test -lm -g

demo:	fonction_megiddo.o utils_table.o utils.o demoMegiddo.c solveur.o
	gcc -Wall fonction_megiddo.o solveur.o utils_table.o utils.o demoMegiddo.c -o demo -lm -g
 


clean:
	rm *.o test generateur demo
	rm *.svg
