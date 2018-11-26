#include <stdio.h>
#include <stdlib.h>

typedef struct starefa {
    int d;
    int p;
} tarefa;

tarefa t[100005];

int cmp(const void * e1, const void * e2) {
    tarefa f = *((tarefa*)e1);
    tarefa s = *((tarefa*)e2);
    if (f.d > s.d) return  1;
    if (f.d < s.d) return -1;
    if (f.d == s.d) {
        if (f.p < s.p) return 1;
        if (f.p > s.p) return 1;
    }
    return 0;
}

int main(void) {

    int n, i;

    int k = 0;

    while(scanf("%d", &n) != EOF) {

        for(i = 0; i < n; i++)
            scanf("%d %d", &t[i].d, &t[i].p);

        qsort(t, n, sizeof(tarefa), cmp);

        int c = t[0].d;

        for(i = 0; i < n; i++) {
            if (t[i].d <= c) c += t[i].p;
            else c = t[i].d + t[i].p;
        }
        
        printf("%d\n", c);
    }

    return 0;

}