CFLAGS=-Wall

test: test.o fonctions_fischer.o
	$(CC) $(CFLAGS) test.o fonctions_fischer.o -lm -o $@

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -lm -o $@

fonctions_fischer.o: fonctions_fischer.c
	$(CC) $(CFLAGS) -c fonctions_fischer.c -lm -o $@

clean:
	rm -f *.o test

