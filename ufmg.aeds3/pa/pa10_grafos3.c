#include<stdio.h>

int g[1005][1005];
int v[1005];
int dp[1005];

int max(int a, int b) { return a > b ? a : b; }
void iniciagrafo(int n);
int dfs(int i, int n);

int main(void) {
    
    int n, m, mi, i, j;
    
    while(scanf("%d", &n) != EOF) {
        
        iniciagrafo(n);
        
        for(i = 0; i < n; i++) {
            scanf("%d", &m);
            for(j = 0; j < m; j++) {
                scanf("%d", &mi);
                g[i][--mi] = 1;
            }
        }
        
        int a = 0;
        
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) v[j] = 0;
            int tmp = dfs(i, n);
            //printf("%d %d\n", i, tmp);
            if (tmp == -1) { a = -1; break; }
            if (tmp > a) a = tmp;
        }
        
        printf("%d\n", a);
        
    }
    
    return 0;
    
}

void iniciagrafo(int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        v[i] = dp[i] = 0;
        for(j = i; j < n; j++)
            g[i][j] = g[j][i] = 0;
    }
}

int dfs(int i, int n) {
    
    if (dp[i]) return dp[i];
    
    int k, d = 1;
    
    v[i] = 1;
    
    for(k = 0; k < n; k++) {
        if (i != k && g[i][k]) {
            if (v[k] == 1) {
                return -1;   
            }
            else {
                int tmp = dfs(k, n);
                if (tmp == -1) return -1;
                d = max(d, tmp + 1);
            }
        }
    }
    
    v[i] = 2;
    
    return dp[i] = d;
}