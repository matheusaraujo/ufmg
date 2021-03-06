#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"intervalo.h"
#include"util.h"
#include"matriz.h"

int main(void) {

  int n, m, i, j, sc;
  int* vetor;
  char acao[3];
  intervalo* matriz;

  sc = scanf("%d %d", &n, &m);

  vetor = (int*) malloc(n * sizeof(int));

  for(i = 0; i < n; i++) {
    sc = scanf("%d", vetor + i);
  }

  matriz = m_construir(vetor, n);

  while(m--) {

      sc = scanf("%s %d %d", acao, &i, &j);
      i--; j--;

      if (!strcmp(acao, "Min")) {
        printf("%d\n", m_minimo(matriz, i, j, n));
      }
      else if (!strcmp(acao, "Max")) {
        printf("%d\n", m_maximo(matriz, i, j, n));
      }
      else if (!strcmp(acao, "Sum")) {
        printf("%d\n", m_soma(matriz, i, j, n));
      }
      else if (!strcmp(acao, "Add")) {
        free(matriz);
        matriz = m_incrementar(vetor, i, j, n);
      }
      else if (!strcmp(acao, "Sub")) {
        free(matriz);
        matriz = m_decrementar(vetor, i, j, n);
      }

  }

  free(matriz);

  // evita warning 'unused'
  if (sc == 0)
    printf("erro");

  return 0;
}
