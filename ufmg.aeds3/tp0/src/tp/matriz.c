#include<stdio.h>
#include<stdlib.h>
#include"intervalo.h"
#include"util.h"
#include"matriz.h"

intervalo* m_construir(int* vetor, int n) {

  intervalo* matriz = (intervalo*)malloc((n * n) * sizeof(intervalo));

  for(int i = 0; i < n; i++) {
    matriz[i*n+i].maximo = vetor[i];
    matriz[i*n+i].minimo = vetor[i];
    matriz[i*n+i].soma = vetor[i];

    for(int j = i + 1; j < n; j++) {
      matriz[i*n+j].maximo = matriz[j*n+i].maximo = u_maximo(matriz[i*n+j-1].maximo, vetor[j]);
      matriz[i*n+j].minimo = matriz[j*n+i].minimo = u_minimo(matriz[i*n+j-1].minimo, vetor[j]);
      matriz[i*n+j].soma = matriz[j*n+i].soma = u_soma(matriz[i*n+j-1].soma, vetor[j]);
    }
  }

  return matriz;

}

int m_minimo(intervalo* matriz, int i, int j, int n) {
  return matriz[i*n+j].minimo;
}

int m_maximo(intervalo* matriz, int i, int j, int n) {
  return matriz[i*n+j].maximo;
}

int m_soma(intervalo* matriz, int i, int j, int n) {
  return matriz[i*n+j].soma;
}

intervalo* m_atualizar(int* vetor, int i, int j, int diff, int n) {
  for(int k = i; k <= j; k++)
    vetor[k]+=diff;

  return m_construir(vetor, n);
}

intervalo* m_incrementar(int* vetor, int i, int j, int n) {
  return m_atualizar(vetor, i, j, 1, n);
}

intervalo* m_decrementar(int* vetor, int i, int j, int n) {
  return m_atualizar(vetor, i, j, -1, n);
}

void m_imprimir(intervalo* matriz, int n) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      printf("(%d %d %d) ", matriz[i*n+j].minimo, matriz[i*n+j].maximo, matriz[i*n+j].soma);
    }
    printf("\n");
  }
}
