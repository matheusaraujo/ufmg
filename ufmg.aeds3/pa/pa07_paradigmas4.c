#include <stdio.h>

int n, k;

int p[105]; /* peso */
int c[10]; /* capacidade */

int m[105][105][105][105]; /* matriz dinamica */
 
int max2(int a, int b) { return (a>b) ? a : b; }
int max3(int a, int b, int c) { return max2(max2(a,b),c); }
int max4(int a, int b, int c, int d) { return max2(max2(a,b),max2(c,d)); }

int mochila() {

    int i, c1, c2, c3;

    for(i = 0; i <= n; i++) {
        for(c1 = 0; c1 <= c[1]; c1++) {
            for(c2 = 0; c2 <= c[2]; c2++) {
                for(c3 = 0; c3 <= c[3]; c3++) {
                    if (i == 0)
                        m[i][c1][c2][c3] = 0;
                    else {
                        int a0 = m[i-1][c1][c2][c3];
                        int a1 = a0;
                        int a2 = a0;
                        int a3 = a0;

                        if (p[i-1] <= c1)
                            a1 = p[i-1] + m[i-1][c1-p[i-1]][c2][c3];

                        if (p[i-1] <= c2)
                            a2 = p[i-1] + m[i-1][c1][c2-p[i-1]][c3];

                        if (p[i-1] <= c3)
                            a3 = p[i-1] + m[i-1][c1][c2][c3-p[i-1]];
                        
                        m[i][c1][c2][c3] = max4(a0,a1,a2,a3);
                    }
                }
            }
        }
    }

    return m[n][c[1]][c[2]][c[3]];
}

int main() {

    int i;

    scanf("%d %d", &n, &k);

    for(i = 0; i < n; i++)
        scanf("%d", &p[i]);

    for(i = 1; i <= k; i++)
        scanf("%d", &c[i]);

    for(i = i; i <= 3; i++)
        c[i] = 0;

    printf("%d\n", mochila());
    
    return 0;
}