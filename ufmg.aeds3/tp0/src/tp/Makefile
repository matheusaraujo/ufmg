CC = gcc
CFLAGS1 = -Wall -Wextra -Werror -std=c99 -pedantic -O2
CFLAGS2 = -Wall -Wextra -Werror -std=c99 -pedantic -O2 -g -c

geral: matriz arvore

matriz: main_matriz.o matriz.o intervalo.o util.o
	$(CC) main_matriz.o matriz.o util.o -o matriz

arvore: main_arvore.o arvore.o intervalo.o util.o
	$(CC) main_arvore.o arvore.o util.o -o arvore

main_matriz.o: main_matriz.c
	$(CC) $(CFLAGS2) main_matriz.c

main_arvore.o: main_arvore.c
	$(CC) $(CFLAGS2) main_arvore.c

matriz.o: util.o matriz.h matriz.c
	$(CC) $(CFLAGS2) matriz.c

arvore.o: util.o arvore.h arvore.c
	$(CC) $(CFLAGS2) arvore.c

intervalo.o: intervalo.h
	$(CC) $(CFLAGS2) intervalo.h

util.o: util.h util.c
	$(CC) $(CFLAGS2) util.c

clean:
	rm *.gch
	rm *.o
	rm matriz
	rm arvore
