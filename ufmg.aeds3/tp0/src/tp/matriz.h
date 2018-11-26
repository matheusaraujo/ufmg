#ifndef d_matriz

#define d_matriz
intervalo* m_construir(int* vetor, int n);
int m_minimo(intervalo* matriz, int i, int j, int n);
int m_maximo(intervalo* matriz, int i, int j, int n);
int m_soma(intervalo* matriz, int i, int j, int n);
intervalo* m_incrementar(int* vetor, int i, int j, int n);
intervalo* m_decrementar(int* vetor, int i, int j, int n);
void m_imprimir(intervalo* matriz, int n);

#endif
