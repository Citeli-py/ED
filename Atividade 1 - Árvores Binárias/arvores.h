#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
1- Ler uma árvore de um arquivo;
2- Imprimir a árvore (pré-ordem, em-ordem, pós-ordem e em largura)
3- Verificar se um elemnto x existe
4- Contar o número de elementos na árvore
5- Imprimir os nós folhas
6- Verificar se uma árvore está balanceada
7- Verificar se uma árvore é cheia
8- Imprimir o nivel de um nó
9- Sair*/

typedef struct arvore
{
    int info;
    struct arvore *esq, *dir;
} arvore;

arvore *LerArvore(FILE *arq) //1- Ler uma árvore de um arquivo;
{
    arvore *a;
    char c;
    int n;
    
    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &n);

    if(n==-1)
    {
        fscanf(arq, "%c", &c);
        return NULL;
    }
    else
    {
        a = (arvore*) malloc(sizeof(arvore));
        a->info = n;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq, "%c", &c);
        return a;
    }
}

void Imprimir_pre(arvore *a) //2- Imprimir a árvore (pré-ordem)
{
    if(a != NULL)
    {
        printf("%d ", a->info);
        Imprimir_pre(a->esq);
        Imprimir_pre(a->dir);
    }
}

void Imprimir_ordem(arvore *a) //2- Imprimir a árvore (em-ordem)
{
    if(a != NULL)
    {
        Imprimir_ordem(a->esq);
        printf("%d ", a->info);
        Imprimir_ordem(a->dir);
    }
}

void Imprimir_pos(arvore *a) //2- Imprimir a árvore (pós-ordem)
{
    if(a != NULL)
    {
        Imprimir_pos(a->esq);
        Imprimir_pos(a->dir);
        printf("%d ", a->info);
    }
}

void Imprime_nivel(arvore *a, int x, int nivel)
{
    if(a!=NULL)
    {
        if(x == nivel)
            printf("%d ", a->info);
        else
        {
            Imprime_nivel(a->esq, x, nivel+1);
            Imprime_nivel(a->dir, x, nivel+1);
        }
    }
}

void Imprime_largura(arvore *a)
{
    for(int i=0; i<Altura(a); i++)
    {
        printf("\n");
        Imprime_nivel(a, i, 0);
    }
}

void Imprimir(arvore *a)
{
    int op;
    printf("1- pre-ordem\n2- em-ordem\n3- pos-ordem\n4- largura\n|escolha> ");
    scanf("%d",&op);

    switch (op)
    {
        case 1:
            Imprimir_pre(a);
            break;
        
        case 2:
            Imprimir_ordem(a);
            break;

        case 3:
            Imprimir_pos(a);
            break;
        
        case 4:
            Imprime_largura(a);
            break;

        default:
            printf("Entrada invalida!");
            break;
    }
}

int Existe(arvore *a, int num) //3- Verificar se um elemnto x existe
{
    if(a == NULL)
        return 0;
    else
    {
        if(num == a->info)
            return 1;
        else
        {
            if(Existe(a->esq, num)==1)
                return 1;
            return Existe(a->dir, num);
        }
    }
}

int ContarNos(arvore *a) //4- Contar o número de elementos na árvore
{
    if(a == NULL)
        return 0;
    else
        return 1 + ContarNos(a->esq) + ContarNos(a->dir);
}

void Folhas(arvore *a) //5- Imprimir os nós folhas
{
    if(a != NULL)
    {
        if(a->esq == NULL && a->dir == NULL)
            printf("%d ", a->info);
        Folhas(a->esq);
        Folhas(a->dir);
    }
}

int Altura(arvore *a)
{
    if(a == NULL)
        return 0;
    else
    {
        int he = Altura(a->esq); //Altura da esquerda
        int hd = Altura(a->dir); //Altura da direita
        if(he>hd)
            return he+1;
        else
            return hd+1;
    }
}

int Balanceada(arvore *a) //6- Verificar se uma árvore está balanceada
{
    if(a == NULL)
        return 1;
    else
    {
        int he = Altura(a->esq);
        int hd = Altura(a->dir);
        if(abs(he-hd)<=1)
            return Balanceada(a->esq)*Balanceada(a->dir);
        else
            return 0;
    }
}

int Cheia(arvore *a) //7- Verificar se uma árvore é cheia
{
    // nos = 2^h - 1
    if(ContarNos(a) == pow(2, Altura(a))-1)
        return 1;
    return 0;
}

void NivelNo(arvore *a, int no, int nivel) //8- Imprimir o nivel de um nó
{
    if(a != NULL)
    {
        if(a->info == no)
            printf("Nivel: %d", nivel);
        else
        {
            NivelNo(a->esq, no, nivel+1);
            NivelNo(a->dir, no, nivel+1);
        }
    }
}

void libera_arvore(arvore *a)
{
    if(a != NULL)
    {
        libera_arvore(a->esq);
        libera_arvore(a->esq);
        free(a);
    }
}