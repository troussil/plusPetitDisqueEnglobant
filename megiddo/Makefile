all:	test

fonction_megiddo.o:	fonction_megiddo.c fonction_megiddo.h structure.h
	gcc -c -lm fonction_megiddo.c -o fonction_megiddo.o

utils_table.o:	utils_table.c utils_table.h structure.h
	gcc -c -lm utils_table.c -o utils_table.o
        
        
test:	fonction_megiddo.o utils_table.o testMegiddo.c
	gcc fonction_megiddo.o utils_table.o testMegiddo.c -o test -lm -g


clean:
	rm *.o test
