#include<stdio.h>

int n, m, gmax;
char g[505][505];
int v[505][505];

int max(int a, int b) { return a > b ? a : b; }
void ler();
void iniciar();
int dfs(int i, int j, int d, int* imax, int* jmax);

int main(void) {
    
    while(scanf("%d %d", &n, &m) && n && m) {
        ler();
        
        int i = 0, j = 0, imax, jmax, i1, i2;
        while(g[i][j] != '.') {
            i++;
            if (i == n) i = 0, j++;
        }
        
        int a = dfs(i, j, 0, &imax, &jmax);
        
        iniciar();
        int b = dfs(imax, jmax, 0, &i1, &i2);
        printf("%d\n", b);
    }
    
    return 0;
}

void ler() {
    int i, j;
    gmax = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            v[i][j] = 0;
            scanf(" %c", &g[i][j]);
        }
    }
}

void iniciar() {
    int i, j;
    gmax = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            v[i][j] = 0;
        }
    }
}

int dfs(int i, int j, int d, int* imax, int* jmax) {
    
    int mx = d, tmp;
    v[i][j] = 1;
    
    if (i+1 < n && !v[i+1][j] && g[i+1][j] == '.') {  
        tmp = dfs(i+1, j, d+1, imax, jmax);
        if (tmp > mx) mx = tmp;
    }
    
    if (i > 0 && !v[i-1][j] && g[i-1][j] == '.') {
        tmp = dfs(i-1, j, d+1, imax, jmax);
        if (tmp > mx) mx = tmp;
    }
    
    if (j+1 < m && !v[i][j+1] && g[i][j+1] == '.') {
        tmp = dfs(i, j+1, d+1, imax, jmax);
        if (tmp > mx) mx = tmp;
    }
    
    if (j > 0 && !v[i][j-1] && g[i][j-1] == '.') {
        tmp = dfs(i, j-1, d+1, imax, jmax);
        if (tmp > mx) mx = tmp;
    }
    
    if (mx > gmax) gmax = mx;
    if (d == gmax) *imax = i, *jmax = j;
     
    return mx;
}