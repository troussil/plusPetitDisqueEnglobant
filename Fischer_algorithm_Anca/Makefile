CFLAGS=-Wall

test: test.o hashset.o
	$(CC) $(CFLAGS) test.o hashset.o -o $@

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o $@

hashset.o: hashset.c
	$(CC) $(CFLAGS) -c hashset.c -o $@

clean:
	rm -f *.o test

