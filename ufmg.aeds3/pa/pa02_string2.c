#include<stdio.h>

void imprimirLinha(int a, int n) {
	int i;
	
	for(i = 0; i < (n-a)/2; i++)
		printf(" ");
	
	for(i = 0; i < a; i++)
		printf("*");

	printf("\n");
}

int main(void) {

	int n, i;

	while(scanf("%d", &n) != EOF) {
		for(i = 1; i <= n; i+=2)
			imprimirLinha(i, n);
		imprimirLinha(1, n);
		imprimirLinha(3, n);
		printf("\n");
	}

	return 0;
}