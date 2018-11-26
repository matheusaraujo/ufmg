#ifndef d_vertice
#define d_vertice

#define NAO_USADO 0
#define USADO 1
#define VIZINHO 2

typedef struct s_vertice {
	int id;
	unsigned int peso;
	int estado;
	int v;
	int* vizinhos;
} vertice;

#endif