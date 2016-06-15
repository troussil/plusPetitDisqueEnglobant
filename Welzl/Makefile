all:	test

Welzl.o:	Welzl.c fonctions_resolution_brute.h structures.h
	gcc -c -lm Welzl.c -o Welzl.o

test.o: test.c fonctions_resolution_brute.h structures.h
	gcc -c -lm test.c -o test.o
	
fonctions_resolution_brute.o: fonctions_resolution_brute.c
	gcc -c -lm fonctions_resolution_brute.c -o fonctions_resolution_brute.o              
test:	Welzl.o test.o fonctions_resolution_brute.o structures.h
	gcc -lm Welzl.o test.o fonctions_resolution_brute.o -o  test 


clean:
	rm *.o test
