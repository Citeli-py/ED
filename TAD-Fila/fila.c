#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

#define N 10000

struct fila
{
    int num[N];
    int pos;
};

Fila inicializa()
{
    Fila f = (Fila)malloc(sizeof(struct fila));
    f->pos = 0;
    return f;
}

int vazia(Fila f)
{
    if(f->pos == 0)
        return 1;
    return 0;
}

int cheia(Fila f)
{
    if(f->pos == N)
        return 1;
    return 0;
}

void imprimir(Fila f)
{
    printf("\nFila\n");
    for(int i=0; i<f->pos; i++)
        printf("%d ", f->num[i]);
    printf("\n\n");
}

int add(Fila f, int x)
{
    if(cheia(f))
        return 0;

    f->num[f->pos] = x;
    f->pos++;
    return 1;
}

int rmv(Fila f, int *x)
{
    if(vazia(f))
        return 0;
    *x = f->num[0];
    for(int i=1; i<f->pos; i++)
        f->num[i-1] = f->num[i];
    f->pos--;
    return 1;
}

void libera(Fila f)
{
    free(f->num);
    free(f);
}


