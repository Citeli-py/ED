#include <stdio.h>
#include "listas.h"

/*  
    1. Inserir uma aresta
    2. Remover uma aresta do grafo
    3. Imprimir grafo
    4. Imprimir os graus de entrada e saida de um vertice
    5. Verificar se um grafo é completo
    6. sair
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
    for(int i=1; i<=n; i++)
        libera(g[i]);
    free(g[0]);
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

void menu(Lista **g, int n, int *op)
{
    int origem, destino, custo;
    printf( "1. Inserir uma aresta\n"
            "2. Remover uma aresta do grafo\n"
            "3. Imprimir grafo\n"
            "4. Imprimir os graus de entrada e saida de um vertice\n"
            "5. Verificar se um grafo eh completo\n"
            "6. sair\n> ");
    
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
            if(completo == 1)
                printf("\nO grafo eh completo!\n\n");
            else
                printf("\nO grafo nao eh completo!\n\n");
            break;

        case 6:
            printf("Programa finalizado!\n");
            break;
    
        default:
            printf("\nA operacao %d nao existe, tente outra!\n\n", *op);
            break;
    }
}

int main()
{
    int n, op=0;
    Lista **g;

    printf("Numero de vertices: ");
    scanf("%d", &n);

    g = (Lista **) malloc((n+1)*sizeof(Lista*));
    inicializar(g,n);

    while (op!=6)
        menu(g,n,&op);

    libera_grafo(g, n);
    return 0;
}