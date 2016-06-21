CFLAGS=-Wall

all: test testsUnitaires

test: test.o fonctions_fischer.o
	$(CC) $(CFLAGS) test.o fonctions_fischer.o -lm -o $@

testsUnitaires: testsUnitaires.o fonctions_fischer.o
	$(CC) $(CFLAGS) testsUnitaires.o fonctions_fischer.o -lm -o $@

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -lm -o $@

testsUnitaires.o: testsUnitaires.c
	$(CC) $(CFLAGS) -c testsUnitaires.c -lm -o $@

fonctions_fischer.o: fonctions_fischer.c
	$(CC) $(CFLAGS) -c fonctions_fischer.c -lm -o $@

clean:
	rm -f *.o test testsUnitaires

