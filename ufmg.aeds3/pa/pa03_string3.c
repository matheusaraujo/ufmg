#include<stdio.h>

unsigned long long int potencia2(int n) {
	unsigned long long int r = 1;
	int i = 0;
	while(++i < n)
		r *= 2;
	return r;
}

int main(void) {

	char p[100];

	int k = 0, i, t;
	unsigned long long int c;

	while (fgets(p, sizeof p, stdin) != NULL) {

		t = 0;
		while(p[t] != '\0') {
			t++;
		}

		c = 0;
		for(i = 0; i < t; i++) {
			if (p[i] == 'b')
				c += potencia2((t-i-1));
		}
		
		printf("Palavra %d\n%llu\n\n", ++k, c);
	}

	return 0;

}