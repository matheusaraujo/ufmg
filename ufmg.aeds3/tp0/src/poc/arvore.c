#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MINIMO 0
#define MAXIMO 1
#define SOMA 2

struct celula {
	int maximo;
	int minimo;
	int soma;
};

int getMid(int s, int e) {  return s + (e -s)/2;  }
int fmaximo(int a, int b) {
	return a > b ? a : b;
}

int fminimo(int a, int b) {
	return a < b ? a : b;
}

int fsoma(int a, int b) {
  return a + b;
}

int fentre(int i, int a, int b) {
  return i >= a && i <= b;
}

int* alocaVetor(int n) {
	return (int*) malloc(n * sizeof(int));
}

// ss - vi
// se - vf
void atualizar(struct celula *arvore, int i, int j, int ss, int se, int diff, int si) {

  if (j < ss || i > se)
    return;

  if (ss == se && fentre(se, i, j)) {
    arvore[si].maximo += diff;
    arvore[si].minimo += diff;
    arvore[si].soma += diff;
  }
  else {
    int mid = getMid(ss, se);
    int left = si*2+1;
    int right = si*2+2;

    atualizar(arvore, i, j, ss, mid, diff, left);
    atualizar(arvore, i, j, mid+1, se, diff, right);

    arvore[si].maximo = fmaximo(arvore[left].maximo, arvore[right].maximo);
    arvore[si].minimo = fminimo(arvore[left].minimo, arvore[right].minimo);
    arvore[si].soma = fsoma(arvore[left].soma, arvore[right].soma);

  }

}

void atualizarArvore(int* vetor, int n, struct celula* arvore, int i, int j, int diff) {
  vetor[i] += diff;
  atualizar(arvore, i, j, 0, n-1, diff, 0);
}

void construir(int* vetor, int ss, int se, struct celula* arvore, int si) {
  if (ss == se) {
    arvore[si].maximo = vetor[ss];
    arvore[si].minimo = vetor[ss];
    arvore[si].soma = vetor[ss];
  }
  else {
    int mid = getMid(ss, se);

    int left = si*2+1;
    int right = si*2+2;

    construir(vetor, ss, mid, arvore, left);
    construir(vetor, mid+1, se, arvore, right);

    arvore[si].maximo = fmaximo(arvore[left].maximo, arvore[right].maximo);
    arvore[si].minimo = fminimo(arvore[left].minimo, arvore[right].minimo);
    arvore[si].soma = fsoma(arvore[left].soma, arvore[right].soma);
  }
}

struct celula* construirArvore(int* vetor, int n) {

  int x = (int)(ceil(log2(n)));
  int max_size = 2*(int)pow(2, x) - 1;
  struct celula *arvore = malloc(max_size * sizeof(struct celula));

  construir(vetor, 0, n-1, arvore, 0);

  return arvore;

}

// ss - vi
// se - vf
// qs - i
// qe - j
// si - ind
int sum(struct celula* arvore, int ss, int se, int qs, int qe, int si, int consulta) {
  if (qs <= ss && qe >= se) {
    if (consulta == MINIMO)
      return arvore[si].minimo;
    else if (consulta == MAXIMO)
      return arvore[si].maximo;
    else if (consulta == SOMA)
      return arvore[si].soma;
  }

  if (se < qs || ss > qe)
    return 0;

  int mid = getMid(ss, se);
  int left = si*2+1;
  int right = si*2+2;

  return sum(arvore, ss, mid, qs, qe, left, consulta) +
    sum(arvore, mid+1, se, qs, qe, right, consulta);
}

int getSum(struct celula* arvore, int n, int qs, int qe, int consulta) {
  return sum(arvore, 0, n - 1, qs, qe, 0, consulta);
}

int main(void) {

  int n, m, i, j, k;
  int* vetor;
  char acao[3];
  struct celula* arvore;

  scanf("%d %d", &n, &m);

  vetor = alocaVetor(n);

  for(i = 0; i < n; i++) {
		scanf("%d", vetor + i);
	}

  arvore = construirArvore(vetor, n);

  for(i = 0; i < m; i++) {
		scanf("%s %d %d", acao, &j, &k);

    j--;
    k--;

    if (strcmp(acao, "Max") == 0)
      printf("%d\n", getSum(arvore, n, j, k, MAXIMO));
		else if(strcmp(acao, "Min") == 0)
      printf("%d\n", getSum(arvore, n, j, k, MINIMO));
		else if (strcmp(acao, "Sum") == 0)
			printf("%d\n", getSum(arvore, n, j, k, SOMA));
		else if (strcmp(acao, "Add") == 0)
      atualizarArvore(vetor, n, arvore, j, k, 1);
    else if (strcmp(acao, "Sub") == 0)
      atualizarArvore(vetor, n, arvore, j, k, -1);

  }

  free(vetor);

  return 0;
}
