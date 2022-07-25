#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N 1000

struct elem
{
    int key;
    void *info;
};

struct heap
{
    struct elem elemento[N];
    int totalElementos;
};

typedef struct heap *Heap;

Heap inicializar()
{
    Heap h = (Heap) malloc(sizeof(struct heap));
    h->totalElementos = 0;
    for(int i=0; i<N; i++)
        h->elemento[i].info = NULL;
    return h;
}

int indiceFilhoEsq(Heap h, int x)
{
    int indice = (2*x) + 1;
    if(x>=h->totalElementos || indice>= h->totalElementos)
        return -1;
    else
        return indice;
}

int indiceFilhoDir(Heap h, int x)
{
    int indice = (2*x) + 2;
    if(x>=h->totalElementos || indice>= h->totalElementos)
        return -1;
    return indice;
} 

int indicePai(Heap h,int x)
{
    int indice = (int) floor((x-1)/2);
    if(x<=0 || x>= h->totalElementos)
        return -1;
    return indice;
}

void AjustarSubindo(Heap h, int pos)
{
    if(pos!=-1)
    {
        int pai = indicePai(h, pos);
        if(pai != -1)
        {
            if(h->elemento[pos].key < h->elemento[pai].key)
            {
                struct elem aux = h->elemento[pos];
                h->elemento[pos] = h->elemento[pai];
                h->elemento[pai] = aux;
                AjustarSubindo(h, pai);
            }
        }
    }
}

int cheia(Heap h)
{
    if(h->totalElementos<N)
        return 1;
    return 0;
}

int inserir(Heap h, int key, void* x, int size)
{
    if(!cheia(h))
        return 0;

    h->elemento[h->totalElementos].key = key;
    h->elemento[h->totalElementos].info = (void*) malloc(size);
    memcpy(h->elemento[h->totalElementos].info, x, size);
    h->totalElementos ++;
    AjustarSubindo(h, h->totalElementos-1);

    return 1;
}


void AjustarDescendo(Heap h, int pos)
{
    if(pos != -1 && indiceFilhoEsq(h, pos) != -1)
    {
        int indiceMaiorFilho = indiceFilhoEsq(h, pos);
        if(indiceFilhoDir(h, pos) != -1 && h->elemento[indiceFilhoDir(h, pos)].key<h->elemento[indiceMaiorFilho].key)
            indiceMaiorFilho = indiceFilhoDir(h,pos);
            
        if(h->elemento[indiceMaiorFilho].key<h->elemento[pos].key)
        {
            struct elem aux = h->elemento[pos];
            h->elemento[pos] = h->elemento[indiceMaiorFilho];
            h->elemento[indiceMaiorFilho] = aux;
            AjustarDescendo(h, indiceMaiorFilho);
        }
    }
}

int remover(Heap h, int *key, void *x, int size)
{
    if(h->totalElementos<=0)
        return 0;

    if(h->totalElementos!=0)
    {
        struct elem retorno = h->elemento[0];
        *key = retorno.key;
        memcpy(x, retorno.info, size);
        h->elemento[0] = h->elemento[h->totalElementos-1];
        h->totalElementos --;
        AjustarDescendo(h, 0);
    }

    return 1;
}

void print(Heap h, void f(void* info))
{
    printf("\n");
    for(int i=0; i<h->totalElementos; i++)
    {
        printf("key: %d\n", h->elemento[i].key);
        f(h->elemento[i].info);
    }
    printf("\n");
}

void destruir(Heap h)
{
    for(int i=0; i<h->totalElementos; i++)
        free(h->elemento[i].info);
    free(h);
}