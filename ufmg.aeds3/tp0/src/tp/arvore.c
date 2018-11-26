#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include"intervalo.h"
#include"util.h"
#include"arvore.h"

#define MINIMO 0
#define MAXIMO 1
#define SOMA 2

int a_tamanho(int n) {
  int c = 1;
  int t = c;
  while(c < n) {
    c = c*2;
    t+=c;
  }
  return t;
}

int a_no_esquerdo(int a) {
  return a*2 + 1;
}

int a_no_direito(int a) {
  return a*2 + 2;
}

// vi - inicio do intervalo
// vf - fim do intervalo
// ind - indice do no atual
void a_construir_recursivo(int* vetor, int vi, int vf, intervalo* arvore, int ind) {

  if(vi == vf) {
    arvore[ind].minimo = vetor[vi];
    arvore[ind].maximo = vetor[vi];
    arvore[ind].soma = vetor[vi];
  }
  else {
    int vm = u_meio(vi, vf);
    int e = a_no_esquerdo(ind);
    int d = a_no_direito(ind);

    a_construir_recursivo(vetor, vi, vm, arvore, e);
    a_construir_recursivo(vetor, vm+1, vf, arvore, d);

    arvore[ind].minimo = u_minimo(arvore[e].minimo, arvore[d].minimo);
    arvore[ind].maximo = u_maximo(arvore[e].maximo, arvore[d].maximo);
    arvore[ind].soma = u_soma(arvore[e].soma, arvore[d].soma);

  }

}

intervalo* a_construir(int* vetor, int n) {

  int tamanho = a_tamanho(n);

  intervalo* arvore = (intervalo*)malloc(tamanho * sizeof(intervalo));

  a_construir_recursivo(vetor, 0, n-1, arvore, 0);

  return arvore;

}

// vi - inicio do intervalo corrente
// vf - fim do intervalo corrente
// i - inicio do intervalo de consulta
// j - fim do intervalo de consulta
// ind - indice do no atual
int a_consulta(intervalo* arvore, int vi, int vf, int i, int j, int ind, int consulta) {
  if (vf < i || vi > j) {
    if (consulta == MINIMO) return INT_MAX;
    else if (consulta == MAXIMO) return INT_MIN;
    else if (consulta == SOMA) return 0;
    else return 0;
  }
  else if (i <= vi && j >= vf) {
    if (consulta == MINIMO) return arvore[ind].minimo;
    else if (consulta == MAXIMO) return arvore[ind].maximo;
    else if (consulta == SOMA) return arvore[ind].soma;
    else return 0;
  }
  else {
    int vm = u_meio(vi, vf);
    int e = a_no_esquerdo(ind);
    int d = a_no_direito(ind);

    int e_c = a_consulta(arvore, vi, vm, i, j, e, consulta);
    int d_c = a_consulta(arvore, vm+1, vf, i, j, d, consulta);

    if (consulta == MINIMO) return u_minimo(e_c, d_c);
    else if (consulta == MAXIMO) return u_maximo(e_c, d_c);
    else if (consulta == SOMA) return u_soma(e_c, d_c);
    else return 0;
  }

}

int a_minimo(intervalo* arvore, int i, int j, int n) {
  return a_consulta(arvore, 0, n-1, i, j, 0, MINIMO);
}

int a_maximo(intervalo* arvore, int i, int j, int n) {
  return a_consulta(arvore, 0, n-1, i, j, 0, MAXIMO);
}

int a_soma(intervalo* arvore, int i, int j, int n) {
  return a_consulta(arvore, 0, n-1, i, j, 0, SOMA);
}

// vi - inicio do intervalo corrente
// vf - fim do intervalo corrente
// i - inicio do intervalo de atualizacao
// j - fim do intervalo de atualizacao
// ind - indice do no atual
void a_atualizar(intervalo* arvore, int vi, int vf, int i, int j, int ind, int diff) {
  if (vf < i || vi > j) {
    return;
  }
  else if (vi == vf && u_entre(vi, i, j)) {
    arvore[ind].maximo += diff;
    arvore[ind].minimo += diff;
    arvore[ind].soma += diff;
  }
  else {
    int vm = u_meio(vi, vf);
    int e = a_no_esquerdo(ind);
    int d = a_no_direito(ind);

    a_atualizar(arvore, vi, vm, i, j, e, diff);
    a_atualizar(arvore, vm+1, vf, i, j, d, diff);

    arvore[ind].maximo = u_maximo(arvore[e].maximo, arvore[d].maximo);
    arvore[ind].minimo = u_minimo(arvore[e].minimo, arvore[d].minimo);
    arvore[ind].soma = u_soma(arvore[e].soma, arvore[d].soma);

  }

}

void a_incrementar(intervalo* arvore, int i, int j, int n) {
  a_atualizar(arvore, 0, n-1, i, j, 0, 1);
}

void a_decrementar(intervalo* arvore, int i, int j, int n) {
  a_atualizar(arvore, 0, n-1, i, j, 0, -1);
}

void a_imprimir(intervalo* arvore, int n) {
  int tamanho = a_tamanho(n);

  for(int i = 0; i < tamanho; i++) {
    printf("(%d %d %d)\n", arvore[i].minimo, arvore[i].maximo, arvore[i].soma);
  }
}
