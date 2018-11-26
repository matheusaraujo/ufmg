#include"vertice.h"

#ifndef d_grafo
#define d_grafo

typedef struct s_grafo{
	int v;
	vertice* vertices;
} grafo;

void iniciar_grafo(grafo* g, int v);
void adicionar_vertice(grafo* g, int i, int p);
void adicionar_aresta(grafo* g, int x, int y);
void marcar_vizinho(grafo* g, int id);
void reiniciar_grafo(grafo* g);

#endif