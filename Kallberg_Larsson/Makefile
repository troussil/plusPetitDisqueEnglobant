#Declaration des variables
CC= gcc
CFLAGS= -Wall -g

#Commandes

all: test_improved_pruning test_updateball_methods ApxSolver

###

test_improved_pruning: improved_pruning.o test_improved_pruning.o updateball_methods.o
	$(CC) $(CFLAGS) $^ -lm -o $@

test_updateball_methods: updateball_methods.o test_updateball_methods.o improved_pruning.o
	$(CC) $(CFLAGS) $^ -lm -o $@

ApxSolver: ApxSolver.o updateball_methods.o improved_pruning.o resolution_brute.o fonctions_resolution_brute.o
	$(CC) $(CFLAGS) $^ -lm -o $@


###

improved_pruning.o: improved_pruning.c
	$(CC) -c $(CFLAGS) improved_pruning.c -lm -o $@

test_improved_pruning.o: test_improved_pruning.c
	$(CC) -c $(CFLAGS) $< -lm -o $@

updateball_methods.o: updateball_methods.c
	$(CC) -c $(CFLAGS) updateball_methods.c -lm -o $@

test_updateball_methods.o: test_updateball_methods.c
	$(CC) -c $(CFLAGS) $< -lm -o $@

ApxSolver.o: ApxSolver.c
	$(CC) -c $(CFLAGS) $< -lm -o $@


#

resolution_brute.o: ../resolution_brute.c
	$(CC) -c $(CFLAGS) ../resolution_brute.c -lm -o $@

fonctions_resolution_brute.o: ../fonctions_resolution_brute.c
	$(CC) -c $(CFLAGS) ../fonctions_resolution_brute.c -lm -o $@



#Nettoyage
clean: 
	rm -f *.o
	rm -f *~
	rm test_improved_pruning test_updateball_methods ApxSolver 
