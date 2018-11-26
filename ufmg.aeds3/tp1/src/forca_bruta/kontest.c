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
		pc[i] = 0;
	return pc;
}

void k_calcular(float* p, unsigned int bm, float* pc1, float* pc2, int n, int nc) {

	for(int i = 0; i < n; i++) {

		unsigned int ii = k_potencia_2(i);

		if (bm & ii) {

			/* subconjunto sem o elemento i */
			unsigned int bm1 = bm;
			bm1 = bm1 & ~ii;
			
			k_calcular_interno(p, bm, bm1, pc1, pc2, i, n, nc);
			
			k_calcular(p, bm1, pc1, pc2, n, nc-1);
			
		}
	}
}

void k_calcular_interno(float* p, unsigned int bm, unsigned int bm1, float* pc1, float *pc2, int i, int n, int nc) {
	
	if (nc == 1)
		return;

	float pa = 0;

	for(int k = 0; k < n; k++) {
		if(bm1 & k_potencia_2(k) && k != i)
			pa += p[k*n+i];
	}

	float pp = k_calcular_probabilidade_partida(nc);

	pc2[bm1] = pc2[bm] * pa * pp;
    pc1[bm1] += pc2[bm] * pa * pp;

}