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
	bm - indice de bitmap do conjunto atual
	pc - vetor de probabilidades dos conjuntos
	n - n do problema
*/
void k_calcular(float* p, unsigned int bm, float* pc1, int n);

#endif