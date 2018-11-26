#include<stdio.h>

int calculaPeso(char *nome) {
	int i = 0;
	int p = 0;
	while(nome[i] != '\0') {
		p += nome[i];
		i++;
	}
	return p;
}

int main(void) {

	int n, i;
	char nome[100005][15];

	int p[100005];

	while(scanf("%d", &n) && n != 0) {

		long long sb = 0; // somatorio de b, sem considerar peso
		long long timeb = 0; // time b, soma considerando peso

		for(i = 1; i <= n; i++) {
			scanf("%s", nome[i]);
			p[i] = calculaPeso(nome[i]);
			sb += p[i];
			timeb += p[i]*i;
		}

		int s = 0;
		long long sa = 0; // somatorio de a, sem considerar peso
		long long timea = 0; // time a, soma considerando peso

		for(i = 1; i <= n; i++) {
			timeb -= sb;
			sb -= p[i];

			sa += p[i];
			timea += sa;

			if (timea == timeb) s = i; 

			if (timea >= timeb) break;
		}

		if (s)
			printf("%s\n", nome[s]);
		else
			printf("Impossibilidade de empate.\n");

	}

	return 0;

}