#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

/*
1- Ler uma árvore de um arquivo;
2- Imprimir a árvore (pré-ordem, em-ordem, pós-ordem e em largura)
3- Verificar se um elemento x existe
4- Imprimir o nivel de um nó x
5- Imprimir as folhas menores que um valor x
6- Inserir um nó x na árvore
7- Remover um nó x da árvore
8- Sair*/

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

int altura(arvore *a)
{
    if(a == NULL)
        return 0;
    else
    {
        int he = altura(a->esq); //altura da esquerda
        int hd = altura(a->dir); //altura da direita
        if(he>hd)
            return he+1;
        else
            return hd+1;
    }
}

void inc(int *pos, int size) //Incremento das posições 
{
    *pos = (*pos+1)%size;
}

void Imprime_largura(arvore *a) //2- Imprimir a árvore (pós-ordem)
{
    int size = pow(2,altura(a));
    arvore *vet[100];
    int posFila=0, tamFila=1;
    vet[0] = a;
    while(posFila<tamFila)
    {
        arvore *aux = vet[posFila];
        inc(&posFila, size);
        printf("%d ", aux->info);
        if(aux->esq != NULL)
        {
            vet[tamFila] = aux->esq;
            inc(&tamFila, size);
        }
        if(aux->dir != NULL)
        {
            vet[tamFila] = aux->dir;
            inc(&tamFila, size);
        }
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
            if(num < a->info)
                return Existe(a->esq, num);
            return Existe(a->dir, num);
        }
    }
}

void Folhas(arvore *a, int num) //5- Imprimir as folhas menores que um valor x
{
    if(a != NULL)
    {
        if(a->esq == NULL && a->dir == NULL && a->info < num)
            printf("%d ", a->info);
        
        else if(num <= a->info)
            Folhas(a->esq, num);
        else
        {
            Folhas(a->esq, num);
            Folhas(a->dir, num);
        }
    }
}

void NivelNo(arvore *a, int no, int nivel) //4- Imprimir o nivel de um nó x
{
    if(a != NULL)
    {
        if(a->info == no)
            printf("Nivel: %d", nivel);
        else if(no < a->info)
            NivelNo(a->esq, no, nivel+1);
        else
            NivelNo(a->dir, no, nivel+1);
    }
}

// Balanceamento
arvore *RotacaoEsqSimples(arvore *p)
{
    arvore *b = p->dir;
    p->dir = b->esq;
    b->esq = p;
    return b;
}

arvore *RotacaoDirSimples(arvore *p)
{
    arvore *b = p->esq;
    p->esq = b->dir;
    b->dir = p;
    return b;
}

arvore *RotacaoEsqDupla(arvore *p)
{
    p->dir = RotacaoDirSimples(p->dir);
    p = RotacaoEsqSimples(p);
    return p;
}

arvore *RotacaoDirDupla(arvore *p)
{
    p->esq = RotacaoEsqSimples(p->esq);
    p = RotacaoDirSimples(p);
    return p;
}

arvore *RotacaoEsq(arvore *p)
{
    int he = altura(p->esq);
    int hd = altura(p->dir);
    if (abs(hd - he) > 1)
    {
        arvore *b = p->dir;
        he = altura(b->esq);
        hd = altura(b->dir);
        if (he > hd)
            p = RotacaoEsqDupla(p);
        else
            p = RotacaoEsqSimples(p);
    }
    return p;
}

arvore *RotacaoDir(arvore *p)
{
    int he = altura(p->esq);
    int hd = altura(p->dir);
    if (abs(hd - he) > 1)
    {
        arvore *b = p->esq;
        he = altura(b->esq);
        hd = altura(b->dir);
        if (hd > he)
            p = RotacaoDirDupla(p);
        else
            p = RotacaoDirSimples(p);
    }
    return p;
}

arvore *inserir(arvore *a, int x)
{
    if(a == NULL) //Momento de inserir
    {
        a = (arvore*)malloc(sizeof(arvore));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
    }
    else
    {
        if (x <= a->info)
        {
            a->esq = inserir(a->esq,x);
            a = RotacaoDir(a);
        }
        else
        {
            a->dir = inserir(a->dir,x);
            a = RotacaoEsq(a);
        }
    }
    return a;
}

arvore *remover(arvore *a, int x)
{
    if(a != NULL)
    {
        if(a->info == x)
        {
            //Verificar se é folha
            if(a->esq == NULL && a->dir == NULL)
            {
                free(a);
                return NULL;
            }
            //Verificar se um dos filhos é nulo
            else if (a->esq == NULL || a->dir == NULL)
            {
                arvore *aux;

                if(a->esq == NULL)
                    aux = a->dir;
                else
                    aux = a->esq;
                free(a);
                return aux;
            }
            //Nenhum filho nulo
            else
            {
                arvore *maiorEsq = a->esq;
                while (maiorEsq->dir != NULL)
                    maiorEsq = maiorEsq->dir;
                a->info = maiorEsq->info;
                a->esq = remover(a->esq,a->info);
                a = RotacaoEsq(a);
            }
        }
        else if (x < a->info)
        {
            a->esq = remover(a->esq, x);
            a = RotacaoEsq(a);
        }
        else
        {
            a->dir = remover(a->dir, x);
            a = RotacaoDir(a);
        }
    }
    return a;
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