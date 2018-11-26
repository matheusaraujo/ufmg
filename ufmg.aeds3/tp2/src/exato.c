#include<stdio.h>
#include"vertice.h"
#include"grafo.h"

int eh_conjunto_dominante(grafo *g);
void exato(grafo* g);
int potencia2(int n) { return n ? 2 << (n-1) : 1; }

int main(void) {
	
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

	exato(&g);

	if (!sc) printf("error\n");

	return 0;	
}

void exato(grafo* g) {

	int p2 = potencia2(g->v);
	long long int max = 0;
	int cmax = 0;
	int imax = 0;

	for(int i = 0; i < p2; i++) {
		
		reiniciar_grafo(g);
		
		long long int peso = 0;
		int v = 1;
		int c = 0;

		for(int j = 0; j < g->v; j++) {
			int p = potencia2(j);
			if (i & p) {
				c++;
				if (g->vertices[j].estado != NAO_USADO) {
					v = 0;
					break;
				}

				peso += g->vertices[j].peso;
				g->vertices[j].estado = USADO;

				for(int k = 0; k < g->vertices[j].v; k++)
					marcar_vizinho(g, g->vertices[j].vizinhos[k]);
			}
		}

		if (v && peso > max) { 
			cmax = c;
			max = peso;
			imax = i;
		}

	}

	printf("%d %lld\n", cmax, max);

	for(int i = 0; i < g->v; i++) {
		int p = potencia2(i);
		if (imax & p) printf("%d ", i+1);
	}

	printf("\n");
}

