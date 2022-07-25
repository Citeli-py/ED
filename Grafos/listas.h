#include <stdio.h>
#include <stdlib.h>

typedef struct Lista
{
    int destino, custo;
    struct Lista *prox;
}Lista;

Lista *Cria_elemento(int destino, int custo)
{
    Lista *resp = (Lista *)malloc(sizeof(Lista));
    resp->destino = destino;
    resp->custo = custo;
    resp->prox = NULL;
    return resp;
}

Lista *inicializa()
{
    return NULL;
}

int tamanho(Lista *lista)
{
    int tam=0;
    Lista *aux = lista;
    for (Lista *aux = lista; aux != NULL; aux=aux->prox)
        tam++;

    return tam;
}

int repete(Lista *lista, int num)
{
    int rep=0;
    Lista *aux = lista;
    for (Lista *aux = lista; aux != NULL; aux=aux->prox)
        if(aux->destino == num)
            rep++;
    return rep;
}

Lista *Busca(Lista *lista, int destino)
{
    Lista *aux = lista;
    while (aux !=NULL && aux->destino != destino)
        aux = aux->prox;
    return aux;
}

Lista *Remove(Lista *lista, int destino)
{
    Lista *ant = lista;
    Lista *aux = ant->prox;
    if(ant->destino == destino)
    {
        lista = aux;
        free(ant);
    }
    else
    {
        while(aux != NULL && aux->destino != destino)
        {
            ant = aux;
            aux = aux->prox;
        }
        if(aux != NULL)
        {
            ant->prox = aux->prox;
            free(aux);
        }
    }
    return lista;
}

Lista *insere (Lista * lista, int destino, int custo)
{
    Lista *novo = Cria_elemento(destino, custo);
    novo->prox = lista;
    lista = novo;
    return lista;
}

void imprime (Lista * lista)
{
    Lista * p; /* variável auxiliar para percorrer a lista */
    for (p = lista; p != NULL; p = p->prox)
        printf("->%d(%d)", p->destino, p->custo);
}

void libera (Lista* lista)
{
    Lista* p = lista;
    while (p != NULL)
    {
        Lista* t = p->prox; 
        free(p); /* libera a memória apontada por p */
        p = t; /* faz p apontar para o próximo */
    }
}