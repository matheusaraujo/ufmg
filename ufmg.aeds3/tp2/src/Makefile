CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O2 -g -c

general: heuristica exato

exato: exato.o grafo.o
	$(CC) exato.o grafo.o -o exato

exato.o: exato.c grafo.o vertice.o
	$(CC) $(CFLAGS) exato.c

heuristica: heuristica.o grafo.o
	$(CC) heuristica.o grafo.o -o heuristica

heuristica.o: heuristica.c grafo.o vertice.o
	$(CC) $(CFLAGS) heuristica.c

grafo.o: grafo.h grafo.c vertice.o
	$(CC) $(CFLAGS) grafo.c

vertice.o: vertice.h
	$(CC) $(CFLAGS) vertice.h

clean:
	rm *.gch
	rm *.o
	rm heuristica
	rm exato