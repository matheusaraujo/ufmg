#include<stdio.h>

int g[2005][2005];
int gt[2005][2005];

int v[2005];

int conn(int n);
void dfs(int i, int n, char ig);

int main(void) {
  
  int n, m, i, j, vv, ww, pp;
  
  while(scanf("%d %d", &n, &m) && n && m) {
    
    for(i = 0; i < n; i++) {
      v[i] = 0;
      for(j = 0; j < n; j++)
        g[i][j] = gt[i][j] = 0;
    }
        
    while(m--) {
      scanf("%d %d %d", &vv, &ww, &pp);
      vv--; ww--;
      if (pp == 1)
        g[vv][ww] = gt[ww][vv] = 1;
      else if (pp == 2)
        g[vv][ww] = g[ww][vv] = gt[vv][ww] = gt[ww][vv] = 1;
    }
    
    printf("%d\n", conn(n));
      
  }
  
  return 0;
}

int conn(int n) {
  
  int i;
  dfs(1, n, 'g');
  
  for(i = 0; i < n; i++) {
    if (!v[i]) return 0;
    v[i] = 0;
  }
  
  dfs(1, n, 't');
  
  for(i = 0; i < n; i++)
    if (!v[i]) return 0;
    
  return 1;
    
}

void dfs(int i, int n, char ig) {
  
  int k;
  v[i] = 1;
  
  for(k = 0; k < n; k++) {
    if (!v[k]) {
      if (ig == 'g' && g[i][k]) {
        dfs(k, n, ig);
      }
      else if (ig == 't' && gt[i][k]) {
        dfs(k, n, ig);
      }
    }
  }
}
