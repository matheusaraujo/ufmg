#include<stdio.h>

int x[55]; /* poder de destruicao */
int y[55]; /* peso */
int m[55][105]; /* matriz dinamica */

int max(int a, int b) { return a > b ? a : b; }

int mochila(int n, int r, int k) {
    int i, j;
    
    for(i = 0; i <= n; i++)
        m[i][0] = 0;
    
    for(j = 0; j <= k; j++)
        m[0][j] = 0;
    
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= k; j++) {
            if (y[i] > j)
                m[i][j] = m[i-1][j];
            else
                m[i][j] = max(m[i-1][j], m[i-1][j-y[i]] + x[i]);
        }
    }
    
    return m[n][k] >= r;
    
}

int main(void) {
    
    int t, n, k, r, i;
    
    scanf("%d", &t);
    
    while(t--) {
        
        scanf("%d", &n);
        
        for(i = 1; i <= n; i++)
            scanf("%d %d", &x[i], &y[i]);
            
        scanf("%d", &k);
        scanf("%d", &r);
        
        if (mochila(n, r, k))
            printf("Missao completada com sucesso\n");
        else
            printf("Falha na missao\n");
        
    }
    
    return 0;
    
}