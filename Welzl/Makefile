all:	Test solveurWelzl generateur 

fonctions_Welzl.o:	fonctions_Welzl.c fonctions_resolution_brute.h structures.h
	gcc -c fonctions_Welzl.c -o fonctions_Welzl.o

Test.o: Test.c fonctions_resolution_brute.h structures.h
	gcc -c Test.c -o Test.o
	
fonctions_resolution_brute.o: fonctions_resolution_brute.c 
	gcc -c fonctions_resolution_brute.c -o fonctions_resolution_brute.o 

resolution_brute.o:resolution_brute.c
	gcc -c resolution_brute.c -o resolution_brute.o	
	    
solveurWelzl.o: solveurWelzl.c structures.h fonctions_resolution_brute.h fonctions_Welzl.h
	gcc -c solveurWelzl.c -o solveurWelzl.o

generateur.o: generateur.c
	gcc -c generateur.c -o generateur.o
		
generateur: generateur.o
	gcc generateur.o -o generateur

#solveur.o:	solveur.c structures.h fonctions_resolution_brute.h resolution_brute.h
#	gcc -c solveur.c -o solveur.o

#solveur:	solveur.o resolution_brute.o fonctions_resolution_brute.o structures.h
#	gcc solveur.o resolution_brute.o fonctions_resolution_brute.o -lm -o solveur

	
solveurWelzl: solveurWelzl.o fonctions_Welzl.o fonctions_resolution_brute.o structures.h
	gcc solveurWelzl.o fonctions_Welzl.o fonctions_resolution_brute.o -lm -o solveurWelzl
		         
Test:	fonctions_Welzl.o Test.o fonctions_resolution_brute.o structures.h
	gcc fonctions_Welzl.o Test.o fonctions_resolution_brute.o -lm -o  Test 


clean:
	rm *.o Test generateur solveurWelzl solveur *.svg
