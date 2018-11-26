#include"util.h"

int u_soma(int a, int b) {
  return a + b;
}

int u_maximo(int a, int b) {
  return a > b ? a : b;
}

int u_minimo(int a, int b) {
  return a > b ? b : a;
}

int u_entre(int x, int a, int b) {
  return x >= a && a <= b;
}

int u_meio(int a, int b) {
  return a + (b - a) / 2;
}
