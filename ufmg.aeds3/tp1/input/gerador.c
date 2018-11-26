#include<stdio.h>

int main(void) {

	int n;

	scanf("%d", &n);

	printf("%d\n", n);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if (i != j) printf("0.5000 ");
			else printf("0.0000 ");
		}
		printf("\n");
	}
}