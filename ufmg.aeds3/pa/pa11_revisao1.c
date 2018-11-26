#include<stdio.h>

int fila[55];
int i1, i2;

void iniciar() { i1 = i2 = 0; }

void incluir(int i) { fila[++i2] = i; }

int remover() { return fila[++i1]; }

int fim() { return i2 - i1 == 1; }

int main(void) {
    
    int n, i, a, b;
    
    while(scanf("%d", &n) && n) {
        
        if (n == 1) {
            printf("Discarded cards: ");
            printf("\nRemaining card: 1\n");    
        }
        else {
            iniciar();
        
            for(i = 1; i <= n; i++)
                incluir(i);
                
            printf("Discarded cards: ");
                
            while(1) {
                printf("%d", remover());
                b = remover();
                incluir(b);
                
                if (fim()) break;
                
                printf(", ");
            }
            
            printf("\nRemaining card: %d\n", remover());
        
        }
    
    }
    
    return 0;
}