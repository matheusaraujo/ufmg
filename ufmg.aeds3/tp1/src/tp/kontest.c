#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"kontest.h"

unsigned int k_potencia_2(int n) {
    return n ? 2 << (n-1) : 1;
}

float k_calcular_probabilidade_partida(int n) {
	return 2.0 / (n * (n - 1.0));
}

float* k_ler_entrada(int n) {
	int sc = 0;
	float* p = malloc(n * n * sizeof(float));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			sc = scanf("%f", &p[i*n+j]);
		}
	}
	if (!sc) printf("erro");
	return p;
}

void k_imprimir_resultado(float* pc1, int n) {
	for(int i = 0; i < n; i++) {
		printf("%.4f ", pc1[k_potencia_2(i)]);
	}
	printf("\n");
}

float* k_iniciar_prob_conj(int n) {
	int n2 = k_potencia_2(n);
	float* pc = malloc(n2 * sizeof(float));
	for(int i = 0; i < n2; i++) 
		pc[i] = -1;
	return pc;
}

void k_calcular(float* p, unsigned int bm, float* pc, int n) {

	if(pc[bm] != -1)
		return;

	pc[bm] = 0;
	
	for(int k = 0; k < n; k++) {

		/* bitmap para o jogador k */
		unsigned int kk = k_potencia_2(k);

		/* se o jogador k não estiver no subconjunto corrente */
		if (!(kk & bm)) {
			
			k_calcular(p, bm | kk, pc, n);

			int cnt = 1;
			float pp = 0;

			/* calcula a probabilidade do subconjunto corrente */
			for(int j = 0; j < n; j++) {
				unsigned int jj = k_potencia_2(j);
				/* se o jogador j estiver no subconjunto */
				if (jj & bm) {
					pp += p[j*n+k];
					cnt++;
				}
			}

			pc[bm] += pc[bm | kk] * k_calcular_probabilidade_partida(cnt) * pp;

		}
	}

}