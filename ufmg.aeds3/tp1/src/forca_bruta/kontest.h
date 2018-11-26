#ifndef d_kontest

/* eleva um número a 2*/
unsigned int k_potencia_2(int n);

/* dado n participantes, calcula a probabilidade de uma partida */
float k_calcular_probabilidade_partida(int n);

/* leh a matriz de probabilidades da entrada */
float* k_ler_entrada(int n);

/* imprime o resultado */
void k_imprimir_resultado(float* pc1, int n);

/* inicia o vetor de probabilidades dos conjuntos */
float* k_iniciar_prob_conj(int n);

/* 
	calcular 
	-- a partir de um dado conjunto, cria os subconjuntos e chama a funcao k_calcular_interno
	p - matriz de probabilidades
	bm - vetor de bitmap do conjunto atual
	pc1 - vetor de probabilidades 1 dos conjuntos
	pc2 - vetor de probabilidades 2 dos conjuntos
	n - n do problema
	nc - n corrente
*/
void k_calcular(float* p, unsigned int bm, float* pc1, float* pc2, int n, int nc);

/*
	calcular interno
	-- faz o calculo da probabilidade de um dado subconjunto
	p - matriz de probabilidades
	bm - vetor de bitmap do conjunto atual
	pc1 - vetor de probabilidades 1 dos conjuntos
	pc2 - vetor de probabilidades 2 dos conjuntos
	bmi - indice do conjunto de origem
	bm1i - indice do conjunto calculado
	n - n do problema
	nc - n corrente
*/
void k_calcular_interno(float* p, unsigned int bm, unsigned int bm1, float* pc1, float *pc2, int i, int n, int nc);

#endif