#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
    int mat;
    char nome[100];
    char curso[30];
}Aluno;

typedef struct reg
{
    Aluno aluno;
    int disponibilidade;
}reg;

int hash(int key, int size)
{
    return key%size;
}

int primo(int num)
{
    for(int i=2; i<num/2; i++)
        if(num%i==0)
            return 0;
    return 1;
}

int get_size()
{
    int size;
    printf("Tamanho da tabela hash: ");
    scanf("%d", &size);
    while (!primo(size))
        size++;
    
    return size;
}

void inicializar(char *nomeArq, int size)
{
    FILE *arq = fopen(nomeArq, "wb");
    reg a;
    a.disponibilidade = 1;
    for(int i=0; i<size; i++)
        fwrite(&a, sizeof(reg), 1, arq);
    fclose(arq);
}

Aluno cria_aluno()
{
    Aluno a;
    printf("Matricula: ");
    scanf("%d", &a.mat);

    fflush(stdin);
    printf("Nome: ");
    gets(a.nome);

    fflush(stdin);
    printf("Curso: ");
    gets(a.curso);
    return a;
}

int achar_posicao(char *nomeArq, int mat, int size)
{
    int pos = hash(mat, size);
    reg a;
    FILE *arq = fopen(nomeArq, "rb");
    fseek(arq, pos*sizeof(reg), SEEK_SET);
    fread(&a, sizeof(reg),1, arq);
    while (a.disponibilidade == 0)
    {
        pos = (pos+1)%size;
        fseek(arq, pos*sizeof(reg), SEEK_SET);
        fread(&a, sizeof(reg),1,arq);
    }
    fclose(arq);
    return pos;
}

void inserir(char *nomeArq, int size)
{
    reg a;
    a.aluno = cria_aluno();
    int pos = achar_posicao(nomeArq, a.aluno.mat, size);
    FILE *arq = fopen(nomeArq, "r+b");
    a.disponibilidade = 0;
    fseek(arq, pos*sizeof(reg), SEEK_SET);
    fwrite(&a, sizeof(reg), 1, arq);
    fclose(arq);
}


void print_aluno(Aluno a)
{
    printf( "\nMatricula: %d\n"
            "Nome: %s\n"
            "Curso: %s\n", a.mat, a.nome, a.curso);
}

void hash_table(char *nomeArq, int size)
{
    reg a;
    FILE *f = fopen(nomeArq, "rb");
    printf("\n++++++++++++ Hash table ++++++++++++\n");
    for(int i=0; i<size; i++)
    {
        fread(&a, sizeof(reg), 1, f);
        if(a.disponibilidade == 0)
            print_aluno(a.aluno);
    }
    printf("\n++++++++++++++++++++++++++++++++++++\n");
    fclose(f);
}

void busca_aluno(char *nomeArq, int mat, int size)
{
    reg a;
    FILE *f = fopen(nomeArq, "rb");
    int pos = hash(mat, size);
    int pos_i = pos;
    fseek(f, pos*sizeof(reg), SEEK_SET);
    fread(&a, sizeof(reg), 1, f);
    while (a.aluno.mat != mat)
    {
        pos = (pos+1)%size;
        fseek(f, pos*sizeof(reg), SEEK_SET);
        fread(&a, sizeof(reg),1,f);
        if(pos_i == pos)
            break;
    }
    if(a.aluno.mat == mat)
    {
        printf("\nAluno encontrado!");
        print_aluno(a.aluno);
    }
    else
        printf("\nAluno nao existe!\n");
    fclose(f);
}