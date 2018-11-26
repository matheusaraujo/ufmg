#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"intervalo.h"
#include"util.h"
#include"arvore.h"

int main(void) {

  int n, m, i, j, sc;
  int* vetor;
  char acao[3];
  intervalo* arvore;

  sc = scanf("%d %d", &n, &m);

  vetor = (int*) malloc(n * sizeof(int));

  for(i = 0; i < n; i++) {
    sc = scanf("%d", vetor + i);
  }

  arvore = a_construir(vetor, n);

  while(m--) {

      sc = scanf("%s %d %d", acao, &i, &j);
      i--; j--;

      if (!strcmp(acao, "Min")) {
        printf("%d\n", a_minimo(arvore, i, j, n));
      }
      else if (!strcmp(acao, "Max")) {
        printf("%d\n", a_maximo(arvore, i, j, n));
      }
      else if (!strcmp(acao, "Sum")) {
        printf("%d\n", a_soma(arvore, i, j, n));
      }
      else if (!strcmp(acao, "Add")) {
        a_incrementar(arvore, i, j, n);
      }
      else if (!strcmp(acao, "Sub")) {
        a_decrementar(arvore, i, j, n);
      }

  }

  free(arvore);

  // evita warning 'unused'
  if (sc == 0)
    printf("erro");

  return 0;

}
