CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O2 -g -c

kontest: main_kontest.o kontest.o
	$(CC) main_kontest.o kontest.o -o kontest

main_kontest.o: main_kontest.c
	$(CC) $(CFLAGS) main_kontest.c

kontest.o: kontest.h kontest.c
	$(CC) $(CFLAGS) kontest.c

clean:
	rm *.o
	rm kontest