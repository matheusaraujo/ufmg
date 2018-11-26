#include<stdlib.h>
#include"grafo.h"

void iniciar_grafo(grafo* g, int v) {
	g->v = v;
	g->vertices = malloc(v * sizeof(vertice));
}

void adicionar_vertice(grafo* g, int i, int p) {
	g->vertices[i].id = i;
	g->vertices[i].peso = p;
	g->vertices[i].estado = NAO_USADO;
	g->vertices[i].v = 0;
	g->vertices[i].vizinhos = (int*)malloc(1 * sizeof(int));
}

void adicionar_aresta(grafo* g, int x, int y) {

	g->vertices[x].v++;
	g->vertices[x].vizinhos = (int*)realloc(g->vertices[x].vizinhos, g->vertices[x].v * sizeof(int));
	g->vertices[x].vizinhos[g->vertices[x].v-1] = y;

	g->vertices[y].v++;
	g->vertices[y].vizinhos = (int*)realloc(g->vertices[y].vizinhos, g->vertices[y].v * sizeof(int));
	g->vertices[y].vizinhos[g->vertices[y].v-1] = x;

}

void marcar_vizinho(grafo* g, int id) {
	for(int i = 0; i < g->v; i++) {
		if (g->vertices[i].id == id) {
			g->vertices[i].estado = VIZINHO;
			break;
		}
	}
}

void reiniciar_grafo(grafo* g) {
	for(int i = 0; i < g->v; i++)
		g->vertices[i].estado = NAO_USADO;
}