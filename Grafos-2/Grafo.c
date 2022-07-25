#include <stdio.h>
#include "listas.h"
#define INF 10000
/*  
    1. Inserir uma aresta
    2. Remover uma aresta do grafo
    3. Imprimir grafo
    4. Imprimir os graus de entrada e saida de um vertice
    5. Verificar se um grafo é completo
    6. Imprimir todos os caminhos entre uma origem e um destino
    7. Imprimir o caminho mais curto (com menor número de arestas)
    8. Imprimir o caminho de menor custo (menor soma dos custos das arestas)
    9. sair
*/

void inicializar(Lista **g, int n)
{
    for(int i=0; i<=n; i++)
        g[i] = NULL;
}

void inserir_aresta(Lista **g, int origem, int destino, int custo)
{
    g[origem] = insere(g[origem], destino, custo);
}

void remove_aresta(Lista **g, int origem, int destino)
{
    g[origem] = Remove(g[origem], destino);
}

void imprime_grafo(Lista **g, int n)
{
    for(int i=1; i<=n; i++)
    {
        printf("%d", i);
        imprime(g[i]);
        printf("\n");
    }
}

void libera_grafo(Lista **g, int n)
{
    for(int i=0; i<=n; i++)
        libera(g[i]);
    free(g);
}

int grau_saida(Lista **g, int vertice)
{
    // Numero de arestas que saem do vertice
    return tamanho(g[vertice]);;
}

int grau_entrada(Lista **g, int n, int vertice)
{
    // Numero de arestas que chegam no vertice
    int ge=0;
    for(int i=1; i<=n; i++)
        ge += repete(g[i], vertice);
    return ge;
}

int completo(Lista **g, int n)
{
    int contador=0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(i!=j && repete(g[i], j)>0)
                contador ++;
    if(contador==n*(n-1)) // Total de arestas de um grafo completo sem laços
        return 1;
    return 0;
}

void cria_completo(Lista **g, int n) // Função auxiliar para testar o item 6
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(i!=j)
                inserir_aresta(g,i,j,1);
}

int existe(int *v, int valor, int n)
{
    for(int i=0; i<n; i++)
        if(v[i]==valor)
            return 1;
    return 0;
}

void imprime_vetor(int *v, int n)
{
    for(int i=0; i<n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void caminhos(Lista **g, int b, int *vet, int pos)
{
    if(vet[pos-1]==b)
    {
        printf("\n");
        for(int i=0; i<pos; i++)
            printf("%d ", vet[i]);
    }
    else
    {
        Lista *p=g[vet[pos-1]];
        while (p!=NULL)
        {
            if(!existe(vet, p->destino,pos))
            {
                vet[pos] = p->destino;
                caminhos(g, b, vet, pos+1);
            }
            p = p->prox;
        } 
    }
}

int Custo(int *vet, int n)
{
    int soma=0;
    for(int i=0; i<n;i++)
        soma += vet[i];
    return soma;
}

Lista* caminho_custo(Lista **g, int b, int *vet, int *custos, int pos, Lista *l, int *menor)
{
    if(vet[pos-1]==b)
    {
        int soma = Custo(custos,pos-1);
        if(soma<*menor)
        {
            *menor = soma;
            libera(l); l = NULL;
            for(int i=pos-1; i>=0; i--)
                l = insere(l, vet[i] ,1);
        }
    }
    else
    {
        Lista *p=g[vet[pos-1]];
        while (p!=NULL)
        {
            if(!existe(vet, p->destino,pos))
            {
                custos[pos-1] = p->custo;
                vet[pos] = p->destino;
                l = caminho_custo(g, b, vet, custos, pos+1, l, menor);
            }
            p = p->prox;
        } 
    }
    return l;
}

void caminho_aresta(Lista **g, int dst, int *vet, int pos, int u, int v)
{
    if(vet[pos-1]==dst)
    {
        int aresta = 0;
        for(int i=0; i<pos-1; i++)
        {
            if(vet[i]==u && vet[i+1] == v)
            {
                aresta = 1;
                break; 
            }
        }
        if(aresta==0)
        {
            for(int j=0; j<pos; j++)
                printf("%d ", vet[j]);
            printf("\n");
        }
    }
    else
    {
        Lista *p=g[vet[pos-1]];
        while (p!=NULL)
        {
            if(!existe(vet, p->destino,pos))
            {
                vet[pos] = p->destino;
                caminho_aresta(g, dst, vet, pos+1, u, v);
            }
            p = p->prox;
        } 
    }
}

Lista* caminho_curto(Lista **g, int b, int *vet, int pos, Lista *l)
{
    if(vet[pos-1]==b)
    {
        if( l==NULL || tamanho(l)>pos)
        {
            libera(l);l = NULL;
            for(int i=pos-1; i>=0; i--)
                l = insere(l, vet[i] ,1);
        }
    }
    else
    {
        Lista *p=g[vet[pos-1]];
        while (p!=NULL)
        {
            if(!existe(vet, p->destino,pos))
            {
                vet[pos] = p->destino;
                l = caminho_curto(g, b, vet, pos+1, l);
            }
            p = p->prox;
        } 
    }
    return l;
}

void menu(Lista **g, int n, int *op)
{
    Lista *l = inicializa();
    int origem, destino, custo;
    int *v = (int*) malloc(n*sizeof(int));
    int *v_aux = (int*) malloc(n*sizeof(int));
    printf( "1. Inserir uma aresta\n"
            "2. Remover uma aresta do grafo\n"
            "3. Imprimir grafo\n"
            "4. Imprimir os graus de entrada e saida de um vertice\n"
            "5. Verificar se um grafo eh completo\n"
            "6. Imprimir todos os caminhos entre uma origem e um destino\n"
            "7. Imprimir o caminho mais curto (com menor numero de arestas)\n"
            "8. Imprimir o caminho de menor custo (menor soma dos custos das arestas)\n"
            "9. sair\n> ");
    
    scanf("%d", op);

    switch (*op)
    {
        case 1:
            printf("Origem: ");
            scanf("%d", &origem);
            printf("Destino: ");
            scanf("%d", &destino);
            printf("Custo: ");
            scanf("%d", &custo);
            printf("\n");
            inserir_aresta(g, origem, destino, custo);
            break;
        
        case 2:
            printf("Origem: ");
            scanf("%d", &origem);
            printf("Destino: ");
            scanf("%d", &destino);
            printf("\n");
            remove_aresta(g, origem, destino);
            break;

        case 3:
            printf("\n");
            imprime_grafo(g,n);
            printf("\n");
            break;

        case 4:
            printf("Vertice: ");
            scanf("%d", &origem);
            printf("\nGrau de entrada: %d\nGrau de saida: %d\n\n", grau_entrada(g,n,origem), grau_saida(g,origem));
            break;

        case 5:
            if(completo(g, n) == 1)
                printf("\nO grafo eh completo!\n\n");
            else
                printf("\nO grafo nao eh completo!\n\n");
            break;

        case 6:
            printf("Origem: ");
            scanf("%d", &origem);
            printf("Destino: ");
            scanf("%d", &destino);
            v[0] = origem;
            caminhos(g, destino, v, 1);
            printf("\n\n");
            break;
        
        case 7:
            printf("Origem: ");
            scanf("%d", &origem);
            printf("Destino: ");
            scanf("%d", &destino);
            v[0] = origem;
            l = caminho_curto(g, destino, v, 1, l);
            if(l==NULL)
                printf("\nNao ha caminho de %d para %d\n", origem, destino);
            else
            {
                printf("\nMenor caminho: ");
                imprime_caminhos(l);
            }
            printf("\n\n");
            break;
        
        case 8:
            printf("Origem: ");
            scanf("%d", &origem);
            printf("Destino: ");
            scanf("%d", &destino);
            v[0] = origem;
            custo = INF;
            l = caminho_custo(g, destino, v, v_aux, 1, l, &custo);
            if(custo == INF)
                printf("\nNao ha caminho de %d para %d\n", origem, destino);
            else
            {
                printf("\nMenor custo:(custo: %d)\n", custo);
                imprime_caminhos(l);
            }
            printf("\n\n");
            break;

        case 9:
            printf("Programa finalizado!\n");
            break;
    
        default:
            printf("\nA operacao %d nao existe, tente outra!\n\n", *op);
            break;
    }
    free(v);
    free(v_aux);
    libera(l);
}

int main()
{
    int n, op=0;
    Lista **g;

    printf("Numero de vertices: ");
    scanf("%d", &n);

    g = (Lista **) malloc((n+1)*sizeof(Lista*));
    inicializar(g,n);
    cria_completo(g,n);
    int *v = (int*) malloc(n*sizeof(int));
    v[0] = 1;
    caminho_aresta(g, 5, v, 1, 1, 2);
    /*
    while (op!=9)
        menu(g,n,&op);

    libera_grafo(g, n);*/
    return 0;
}