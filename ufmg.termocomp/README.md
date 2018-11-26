# ufmg.termocomp
atividades da disciplina termocomp - 2018-02 ufmg

## entrada
* linha 1: temperaturas iniciais
* linhas 2 a 13: coeficientes das equacoes

## saida
`epoca,delta,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12`

## algoritmo
```c
while (epoca < MAXEPOCA && delta > EPS) {		
  multiply();
  delta = cdelta(), epoca++;
  copy();
}
```

## compilar
`gcc main.cpp -o main.exe`

## rodar
`main.exe < input.in` ou `main.exe < input.in > output.out`