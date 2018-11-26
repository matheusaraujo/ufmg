#include<stdio.h>
#include<stdlib.h>
#include"kontest.h"

int main(void) {

	int sc = 0, n;

	sc = scanf("%d", &n);

	/* matriz de probabilidades */
	float* p = k_ler_entrada(n);

	if (n == 1) {
		printf("1.0000\n");
	}
	else {

		/* bitmap dos conjuntos */
		unsigned int bm = k_potencia_2(n) - 1;

		/* 1o vetor de probabilidades dos conjuntos */
		float* pc1 = k_iniciar_prob_conj(n);

		/* 2o vetor de probabilidades dos conjuntos */
		float* pc2 = k_iniciar_prob_conj(n);

		/* probabilidade do conjunto inicial */
		pc1[bm] = pc2[bm] = 1;
	
		k_calcular(p, bm, pc1, pc2, n, n);
		k_imprimir_resultado(pc1, n);

		free(pc1);
		free(pc2);
	}

	if (!sc) printf("erro");

	free(p);
	
	return 0;

}