CFLAGS=-Wall

test: test.o hashset.o hashset_itr.o fonctions_fischer.o
	$(CC) $(CFLAGS) test.o hashset.o hashset_itr.o fonctions_fischer.o -lm -o $@

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -lm -o $@

hashset.o: hashset.c
	$(CC) $(CFLAGS) -c hashset.c -lm -o $@
	
hashset_itr.o: hashset_itr.c
	$(CC) $(CFLAGS) -c hashset_itr.c -lm -o $@

fonctions_fischer.o: fonctions_fischer.c
	$(CC) $(CFLAGS) -c fonctions_fischer.c -lm -o $@

clean:
	rm -f *.o test

