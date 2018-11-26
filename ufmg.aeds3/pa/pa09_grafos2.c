#include<stdio.h>
#include<stdlib.h>

struct s_aresta {
	int x;
	int y;
	int z;
} typedef aresta;

aresta a[50005];
int p[40005];

int compare(const void *a, const void *b) {
	return ((aresta*)a)->z - ((aresta*)b)->z;
}

int parent(int i) {
	if (i == p[i]) return i;
	else return parent(p[i]);
}

void setParent(int i, int j) {
	p[i] = p[j];
}

int kruskal(int n) {

	int i, agm = 0;;

	for(i = 0; i < n; i++) {

		int x = parent(a[i].x);
		int y = parent(a[i].y);

		if (x != y) {
			setParent(x, y);
			agm += a[i].z;
		}
	}

	return agm;

}

int main(void) {

	int m, n, i;

	while(scanf("%d %d", &m, &n) && m && n) {

		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].z);
		}

		qsort(a, n, sizeof(aresta), compare);

		for(i = 0; i < m; i++)
			p[i] = i;

		printf("%d\n", kruskal(n));

	}

	return 0;
}