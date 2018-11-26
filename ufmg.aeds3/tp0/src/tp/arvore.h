#ifndef d_arvore

#define d_arvore
intervalo* a_construir(int* vetor, int n);
int a_minimo(intervalo* arvore, int i, int j, int n);
int a_maximo(intervalo* arvore, int i, int j, int n);
int a_soma(intervalo* arvore, int i, int j, int n);
void a_incrementar(intervalo* arvore, int i, int j, int n);
void a_decrementar(intervalo* arvore, int i, int j, int n);
void a_imprimir(intervalo* arvore, int n);

#endif
