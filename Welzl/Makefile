all:	Test

fonctions_Welzl.o:	fonctions_Welzl.c fonctions_resolution_brute.h structures.h
	gcc -c -lm fonctions_Welzl.c -o fonctions_Welzl.o

Test.o: Test.c fonctions_resolution_brute.h structures.h
	gcc -c -lm Test.c -o Test.o
	
fonctions_resolution_brute.o: fonctions_resolution_brute.c
	gcc -c -lm fonctions_resolution_brute.c -o fonctions_resolution_brute.o              
Test:	fonctions_Welzl.o Test.o fonctions_resolution_brute.o structures.h
	gcc -lm fonctions_Welzl.o Test.o fonctions_resolution_brute.o -o  Test 


clean:
	rm *.o Test
