#include<stdio.h>

void imprimirNumero(int n) {
	printf("%d", n);
}

void imprimirNumeroInverso(int n) {
	while (n != 0) {
		printf("%d", n%10);
		n = n/10;
	}
}

int main(void) {

	int c, b, e, i;

	scanf("%d", &c);

	while(c--) {

		scanf("%d %d", &b, &e);

		for(i = b; i <= e; i++)
			imprimirNumero(i);

		for(i = e; i >= b; i--)
			imprimirNumeroInverso(i);

		printf("\n");

	}

	return 0;

}