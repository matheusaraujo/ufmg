#include<stdio.h>
#include<string.h>

#define INDEFINIDO 0
#define MANDANTE 1
#define VISITANTE 2
#define EMPATE 3

struct jogo
{
    int i;
    int j;
};

struct classificacao
{
    char nome[30];
    int indice;
    int pontuacao;
};

char nomes[20][30];
int melhorPosicao[20];
int piorPosicao[20];
int resultados[20][20];
int resultadosSimulados[20][20];
int pontuacao[20];
int n;
struct jogo jogosFaltantes[400];
int totalJogosFaltantes;
struct classificacao classificacaoSimulada[20];

void iniciaResultados();
int encontraNome(char nome[30]);
void defineResultado(int n1, int n2, int gol1, int gol2);
void defineJogosFaltantes();

void simulaResultados(int i);
void calculaClassificacaoSimulada();
void calculaDesempenhoTime();
void calculaPontuacaoSimulada();
void ordenaClassificacaoSimulada();

void imprimeResultados();
void imprimeResultadosSimulados();
void imprimeJogosFaltantes();
void imprimePontuacaoSimulada();

int minimo(int a, int b) { return a < b ? a : b; }
int maximo(int a, int b) { return a > b ? a : b; }

int main(void) {

    int g, gol1, gol2, i;

    char nome1[30];
    char nome2[30];

    int x = 0;

    while(scanf("%d", &n) != EOF) {

        if (n == 0)
            break;

        iniciaResultados();

        for(i = 0; i < n; i++) {
            scanf("%s", nomes[i]);
        }

        scanf("%d", &g);

        for(i = 0; i < g; i++) {
            scanf("%s %s %d %d", nome1, nome2, &gol1, &gol2);
            defineResultado(encontraNome(nome1), encontraNome(nome2), gol1, gol2);
        }

        defineJogosFaltantes();

        simulaResultados(0);

        printf("Group #%d\n", ++x);

        for(i = 0; i < n; i++) {
            printf("%s %d-%d\n", nomes[i], melhorPosicao[i], piorPosicao[i]);
        }

        printf("\n");

    }

    return 0;
}

void iniciaResultados() {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            resultados[i][j] = INDEFINIDO;
            resultadosSimulados[i][j] = INDEFINIDO;
        }
        melhorPosicao[i] = n;
        piorPosicao[i] = 1;
    }
}

void defineResultado(int n1, int n2, int gol1, int gol2) {
    if (gol1 > gol2) 
        resultados[n1][n2] = MANDANTE;
    else if (gol1 < gol2) 
        resultados[n1][n2] = VISITANTE;
    else 
        resultados[n1][n2] = EMPATE;
    resultadosSimulados[n1][n2] = resultados[n1][n2];
}

int encontraNome(char nome[30]) {
    int i;
    for(i = 0; i < n; i++)
        if (strcmp(nomes[i], nome) == 0)
            return i;
    return n;
}

void defineJogosFaltantes() {
    int i, j;
    totalJogosFaltantes = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if (i != j && resultados[i][j] == INDEFINIDO) {
                jogosFaltantes[totalJogosFaltantes].i = i;
                jogosFaltantes[totalJogosFaltantes].j = j;
                totalJogosFaltantes++;
            }
        }
    }
}

void simulaResultados(int i) {
    if (i == totalJogosFaltantes) {
        calculaClassificacaoSimulada();
        calculaDesempenhoTime();
    }
    else {
        resultadosSimulados[jogosFaltantes[i].i][jogosFaltantes[i].j] = MANDANTE;
        simulaResultados(i+1);
        
        resultadosSimulados[jogosFaltantes[i].i][jogosFaltantes[i].j] = VISITANTE;
        simulaResultados(i+1);
        
        resultadosSimulados[jogosFaltantes[i].i][jogosFaltantes[i].j] = EMPATE;
        simulaResultados(i+1);
    }
}

void calculaClassificacaoSimulada() {
    calculaPontuacaoSimulada();
    ordenaClassificacaoSimulada();    
}

void calculaPontuacaoSimulada() {
    int i, j;
    for(i = 0; i < n; i++)
        pontuacao[i] = 0;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if (i != j) {
                if (resultadosSimulados[i][j] == MANDANTE)
                    pontuacao[i]+=3;
                else if (resultadosSimulados[i][j] == VISITANTE)
                    pontuacao[j]+=3;
                else
                    pontuacao[i]++,pontuacao[j]++;
            }
        }
    }

    for(i = 0; i < n; i++) {
        strcpy(classificacaoSimulada[i].nome, nomes[i]);
        classificacaoSimulada[i].indice = i;
        classificacaoSimulada[i].pontuacao = pontuacao[i];
    }
}

void ordenaClassificacaoSimulada() {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if (classificacaoSimulada[i].pontuacao < classificacaoSimulada[j].pontuacao) {                
                struct classificacao tmp = classificacaoSimulada[i];
                classificacaoSimulada[i] = classificacaoSimulada[j];
                classificacaoSimulada[j] = tmp;
            }
        }
    }
}

void calculaDesempenhoTime() {
    int i;
    for(i = 0; i < n; i++) {
        int i1 = i;
        int i2 = i;
        while(classificacaoSimulada[i].pontuacao == classificacaoSimulada[i1].pontuacao && i1 >= 0) i1--;
        while(classificacaoSimulada[i].pontuacao == classificacaoSimulada[i2].pontuacao && i2 < n) i2++;
        int itime = classificacaoSimulada[i].indice;
        melhorPosicao[itime] = minimo(melhorPosicao[itime], i1+2);
        piorPosicao[itime] = maximo(piorPosicao[itime], i2);
    }
}

void imprimeResultados() {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%d ", resultados[i][j]);
        }
        printf("\n");
    }
}

void imprimeResultadosSimulados() {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%d ", resultadosSimulados[i][j]);
        }
        printf("\n");
    }
}

void imprimeJogosFaltantes() {
    int i;
    for(i = 0; i < totalJogosFaltantes; i++)
        printf("%d %d\n", jogosFaltantes[i].i, jogosFaltantes[i].j);
}

void imprimePontuacaoSimulada() {
    int i;
    for(i = 0; i < n; i++)
        printf("%d %s %d\n", classificacaoSimulada[i].indice, classificacaoSimulada[i].nome, classificacaoSimulada[i].pontuacao);
}