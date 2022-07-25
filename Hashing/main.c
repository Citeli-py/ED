#include <stdio.h>
#include <stdlib.h>
#include "hashing.h"
#define bin "hash_table.bin"

/*
    1. Inserir um novo aluno(Matricula, nome, curso)
    2. Imprimir informações de um aluno(Busca pela matricula)
    3. Imprimir tabela hash
    4. sair 
*/

int menu(int size)
{
    int op, aux;
    printf( "\n1. Inserir um novo aluno\n"
            "2. Imprimir informacoes de um aluno\n"
            "3. Imprimir tabela hash\n"
            "4. sair\n> " );

    scanf("%d", &op);
    switch (op)
    {
        case 1:
            inserir(bin, size);
            break;

        case 2:
            printf("Digite a matricula do aluno: ");
            scanf("%d", &aux);
            busca_aluno(bin, aux, size);
            break;

        case 3:
            hash_table(bin, size);
            break;
        
        case 4:
            printf("Programa finalizado!");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
    }
    return op;
}

int main()
{
    int op=0;
    int size = get_size();
    printf("Tamanho real da tabela hash %d elementos\n", size);
    inicializar(bin, size);
    while (op != 4)
        op = menu(size);
    return 0;
}