#include<stdio.h>
#include<stdlib.h>
#include"vertice.h"
#include"grafo.h"

int hcomp (const void *aa, const void *bb);
void heuristica (grafo* g);

int main (void) {

	grafo g;

	int n, m, p, x, y, sc;

	sc = scanf("%d %d", &n, &m);

	iniciar_grafo(&g, n);

	for(int i = 0; i < n; i++) {
		sc = scanf("%d", &p);
		adicionar_vertice(&g, i, p);
	}

	for(int i = 0; i < m; i++) {
		sc = scanf("%d %d", &x, &y);
		x--; y--;
		adicionar_aresta(&g, x, y);
	}

	heuristica(&g);

	if (!sc) printf("error\n");

	return 0;
}

int hcomp (const void *aa, const void *bb) {
	vertice* a = (vertice*) aa;
	vertice* b = (vertice*) bb;
	if (a->peso > b->peso) return -1;
	else if (a->peso < b->peso) return 1;
	else return a->v - b->v;
}

void heuristica (grafo* g) {

	qsort(g->vertices, g->v, sizeof(vertice), hcomp);

	long long int p = 0;
	int c = 0;

	for(int i = 0; i < g->v; i++) {
		if (g->vertices[i].estado == NAO_USADO) {
			c++;
			p += g->vertices[i].peso;
			g->vertices[i].estado = USADO;
			for(int j = 0; j < g->vertices[i].v; j++)
				marcar_vizinho(g, g->vertices[i].vizinhos[j]);
		}
	}

	printf("%d %lld\n", c, p);

	for(int i = 0; i < g->v; i++)
		if (g->vertices[i].estado == USADO)
			printf("%d ", g->vertices[i].id+1);

	printf("\n");

}