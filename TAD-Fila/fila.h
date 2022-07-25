#ifndef Fila_H
#define Fila_H

typedef struct fila *Fila;
int add(Fila p, int x);
int rmv(Fila p, int *x);
void imprimir(Fila p);
Fila inicializa();
void libera(Fila p);
#endif