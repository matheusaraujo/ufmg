#include <stdio.h>
#include <float.h>

#define LEN 12					/* tamanho da matriz */
#define EPS 0.01				/* criterio de parada 1: diferenca entre t[p] e t[p-1] */
#define MAXEPOCA 100			/* criterio de parada 2: iteracoes */

float t[LEN];					/* matriz 1xLEN com temperaturas */
float t1[LEN];					/* matriz 1xLEN com temperaturas em p+1 */
float coefs[LEN][LEN];			/* matriz LENxLEN com coeficientes */
float delta = FLT_MAX;			/* delta de cada iteracao */
int epoca = 0;					/* iteracoes */

void read();					/* le a entrada */
void multiply();				/* multiplica as matrizes */
float cdelta();					/* calcula o delta */
float absolute(float x);		/* valor absoluto */
void copy();					/* copia t1 para t */		

void print0();					/* print inicial */
void printn();					/* print iteracao */

int main(void) {

	read();
	print0();

	while (epoca < MAXEPOCA && delta > EPS) {		
		multiply();		
		delta = cdelta(), epoca++;		
		copy();
		printn();				
	}

	return 0;

}

void read() {
	for(int i = 0; i < LEN; i++)
		scanf("%f", &t[i]);		

	for(int i = 0; i < LEN; i++) {
		for(int j = 0; j < LEN; j++) {
			scanf("%f", &coefs[i][j]);
		}
	}
}

void multiply() {
	for(int i = 0; i < LEN; i++) {
		t1[i] = 0;
		for(int j = 0; j < LEN; j++) {
			t1[i] += t[i] * coefs[i][j];
		}		
	}
}

float absolute(float x) {
	return x > 0 ? x : -x;
}

float cdelta() {
	float d = 0;
	for(int i = 0; i < LEN; i++)
		d += absolute(t[i] - t1[i]);
	return d;
} 

void copy() {
	for(int i = 0; i < LEN; i++)
		t[i] = t1[i];
}

void print0() {
	printf("0,0");
	for(int i = 0; i < LEN; i++)
		printf(",%f", t[i]);
	printf("\n");
}

void printn() {
	printf("%d,%f", epoca, delta);

	for(int i = 0; i < LEN; i++)
		printf(",%f", t1[i]);
	
	printf("\n");
}