#include<stdio.h>
#include<stdlib.h>
#include"kontest.h"

int main(void) {

	int sc = 0, n;

	sc = scanf("%d", &n);

	/* matriz de probabilidades */
	float* p = k_ler_entrada(n);

	/* bitmap dos conjuntos */
	unsigned int bm = k_potencia_2(n) - 1;

	/* vetor de probabilidades dos conjuntos */
	float* pc = k_iniciar_prob_conj(n);

	/* probabilidade do conjunto inicial */
	pc[bm] = 1;

	for(int i = 0; i < n; i++) {
		k_calcular(p, k_potencia_2(i), pc, n);
	}
	
	k_imprimir_resultado(pc, n);

	free(pc);

	if (!sc) printf("erro");

	free(p);
	
	return 0;

}