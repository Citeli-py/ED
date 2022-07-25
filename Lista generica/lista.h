#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct professor
{
    int matricula;
    char nome[100];
    float salario;
} professor;

typedef struct aluno
{
    int matricula;
    char nome[100];
    char curso[30];
    int ano;
} aluno;

typedef struct lista
{
    int tipo;
    void* info;
    struct lista *prox;
}lista;

lista *inicializa()
{
    return NULL;
}

void imprime_aluno(aluno *a) // -> 2
{
    printf("\nAluno\n");
    printf("\nmatricula: %d", a->matricula);
    printf("\nnome: %s", a->nome);
    printf("\ncurso: %s", a->curso);
    printf("\nano: %d", a->ano);
    printf("\n");
}

void imprime_professor(professor *p) // -> 1
{
    printf("\nProfessor\n");
    printf("\nmatricula: %d", p->matricula);
    printf("\nnome: %s", p->nome);
    printf("\nSalario: %.2f", p->salario);
    printf("\n");
}

void imprime(lista *l)
{
    printf("\nLista\n\n");
    for(lista *p = l; p!=NULL; p=p->prox)
    {
        if(p->tipo == 1)
            imprime_professor((professor*) p->info);
        else
            imprime_aluno((aluno*) p->info);
    }
}

void *cria_professor()
{
    professor *p = (professor*) malloc(sizeof(professor));
    printf("\nProfessor\n");
    printf("Matricula: ");
    scanf("%d", &p->matricula);
    printf("Nome: ");
    fflush(stdin);
    gets(p->nome);
    printf("Salario: ");
    scanf("%f", &p->salario);
    return p;
}

void *cria_aluno()
{
    printf("\nAluno\n");
    aluno *a = (aluno*) malloc(sizeof(aluno));
    printf("Matricula: ");
    scanf("%d", &a->matricula);
    printf("Nome: ");
    fflush(stdin);
    gets(a->nome);
    printf("Ano: ");
    scanf("%d", &a->ano);
    printf("Curso: ");
    fflush(stdin);
    gets(a->curso);
    return a;
}

lista *Cria_elemento()
{
    lista *resp = (lista *)malloc(sizeof(lista));
    printf("\n1-Professor\n2-Aluno\n> ");
    scanf("%d", &resp->tipo);
    if(resp->tipo == 1)
        resp->info = cria_professor();
    else
        resp->info = cria_aluno();
    resp->prox = NULL;
    return resp;
}

lista *insere (lista * l)
{
    lista *novo = Cria_elemento();
    novo->prox = l;
    l = novo;
    return l;
}

int get_matricula(lista* l)
{
    if(l->tipo == 1)
        return ((professor*) l->info)->matricula;
    return ((aluno*) l->info)->matricula;
}

void Busca(lista *l, int mat)
{
    int flag=0;
    for(lista *aux = l; aux!=NULL && flag; aux=aux->prox)
        if(get_matricula(aux)==mat)
        {
            flag = 1;
            if(aux->tipo==1)
                imprime_professor((professor*) aux->info);
            else
                imprime_aluno((aluno*) aux->info);
        }

    if(!flag)
        printf("\n\nEssa pessoa nao existe!\n\n");
    
}

lista *Remove(lista *l, int mat)
{
    lista *ant = l;
    lista *aux = ant->prox;

    if(get_matricula(ant) == mat)
    {
        l = aux;
        free(ant);
    }
    else
    {
        while(aux != NULL && get_matricula(aux) != mat)
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
    return l;
}

int conta_alunos(lista *l, char curso[30])
{
    int conta = 0;
    for(lista *aux = l; aux!=NULL; aux=aux->prox)
        if(aux->tipo == 2)
            if( strcmp(((aluno*) aux->info)->curso, curso) == 0)
                conta++;

    return conta;
}

void maiores_salarios(lista *l)
{
    float maior_salario=0;
    professor *p;

    for (lista *aux = l; aux != NULL; aux=aux->prox)
        if(aux->tipo == 1)
        {
            p = (professor*) aux->info;
            if(p->salario > maior_salario)
                maior_salario = p->salario;
        }
    
    printf("\nProfessores com maiores salarios:\n");
    for (lista *aux = l; aux != NULL; aux=aux->prox)
        if(aux->tipo == 1)
        {
            p = (professor*) aux->info;
            if(p->salario == maior_salario)
                imprime_professor(p);
        }
}

void libera (lista* l)
{
    lista* p = l;
    while (p != NULL)
    {
        lista* t = p->prox; 
        free(p->info);
        free(p); /* libera a memória apontada por p */
        p = t; /* faz p apontar para o próximo */
    }
}