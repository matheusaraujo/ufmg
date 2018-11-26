#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct celula {
	int maximo;
	int minimo;
	int soma;
};

int fmaximo(int a, int b) {
	return a > b ? a : b;
}

int fminimo(int a, int b) {
	return a < b ? a : b;
}

int* alocaVetor(int n) {
	return (int*) malloc(n * sizeof(int));
}

struct celula * construirMatriz(int* vetor, int n) {

	int i, j;

	struct celula * matriz = (struct celula *)malloc((n * n) * sizeof(struct celula));

	for(i = 0; i < n; i++) {

		matriz[i*n+i].maximo = vetor[i];
		matriz[i*n+i].minimo = vetor[i];
		matriz[i*n+i].soma = vetor[i];

		for(j = i + 1; j < n; j++) {
			matriz[i*n+j].maximo = matriz[j*n+i].maximo = fmaximo(matriz[i*n+j-1].maximo, vetor[j]);
			matriz[i*n+j].minimo = matriz[j*n+i].minimo = fminimo(matriz[i*n+j-1].minimo, vetor[j]);
			matriz[i*n+j].soma = matriz[j*n+i].soma = matriz[i*n+j-1].soma + vetor[j];
		}
	}

	return matriz;
}

int main(void) {

	int n, m, i, j, k;
	int* vetor;
	struct celula* matriz;
	char acao[3];

	scanf("%d %d", &n, &m);

	vetor = alocaVetor(n);

	for(i = 0; i < n; i++) {
		scanf("%d", vetor + i);
	}

	matriz = construirMatriz(vetor, n);

	for(i = 0; i < m; i++) {
		scanf("%s %d %d", acao, &j, &k);

		j--;
		k--;

		if (strcmp(acao, "Max") == 0)
			printf("%d\n", matriz[j*n+k].maximo);
		else if(strcmp(acao, "Min") == 0)
			printf("%d\n", matriz[j*n+k].minimo);
		else if (strcmp(acao, "Sum") == 0)
			printf("%d\n", matriz[j*n+k].soma);
		else if (strcmp(acao, "Add") == 0) {
			int i1;
			for(i1 = j; i1 <= k; i1++)
				vetor[i1]++;
			free(matriz);
			matriz = construirMatriz(vetor, n);
		}
		else if (strcmp(acao, "Sub") == 0) {
			int i1;
			for(i1 = j; i1 <= k; i1++)
				vetor[i1]--;
			free(matriz);
			matriz = construirMatriz(vetor, n);
		}
	}

	free(vetor);
	free(matriz);

	return 0;
}
