#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int c_pow2(int n) {
    unsigned int b = 1;
    while(n--) b *= 2;
    return b;
}

unsigned int c_pos(int* s, int n) {
    int r = 0;
    for(int i = 0, b = 1; i < n; i++) {
        if(s[i] == 1)
            r += b;
        b *= 2;
    }
    return r;
}

int* copiar(int const* src, size_t len)
{
   int * p = malloc(len * sizeof(int));
   memcpy(p, src, len * sizeof(int));
   return p;
}

void calcular2(int* s1, float* prob_c, float* prob_c2, float* prob, int i, unsigned int is, unsigned int is1, int n, int n1) {
    
    if (n1 == 1)
        return;

    float pj = 2.0 / (n1 * (n1 - 1.0));
    float s = 0;
    
    for(int k = 0; k < n; k++) {
        if(s1[k] == 1 && k != i) {
            s += prob[k*n+i];
        }
    }

    prob_c2[is1] = prob_c2[is] * s * pj;
    prob_c[is1] += prob_c2[is] * s * pj;
}

void calcular(int* s, float* prob_c, float* prob_c2, float* prob, int n, int n1) {

    unsigned int pos = c_pos(s, n);

    if (pos == 0)
        return;

    for(int i = 0; i < n; i++) {
        if (s[i] == 1) {
            int* s1 = copiar(s, n);
            s1[i] = 0;
            unsigned int pos1 = c_pos(s1, n);
            calcular2(s1, prob_c, prob_c2, prob, i, pos, pos1, n, n1);
            calcular(s1, prob_c, prob_c2, prob, n, n1-1);
            free(s1);
        } 
    }

}

int main(void) {

    int n;

    scanf("%d", &n);

    float* prob;
    prob = malloc(n * n * sizeof(float));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%f", &prob[i*n + j]);
        }
    }

    int* s;
    s = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
        s[i] = 1;

    int size = c_pow2(n);

    float* prob_c;
    prob_c = malloc(size * sizeof(float));

    float* prob_c2;
    prob_c2 = malloc(size * sizeof(float));

    for(unsigned int i = 1; i < size; i++) {
        prob_c[i] = 0;
    }

    prob_c[c_pos(s,n)] = prob_c2[c_pos(s,n)] = 1;

    calcular(s, prob_c, prob_c2, prob, n, n);

    for(int i = 0; i < n; i++) {
        unsigned int a = c_pow2(i);
        printf("%.4f ", prob_c[a]);
    }

    printf("\n");

    free(prob);
    free(s);
    free(prob_c);

    return 0;
}
