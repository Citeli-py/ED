#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/*
    1. Inserir uma pessoa na lista
    2. Remover pela matricula
    3. Buscar pela matricula - caso ache, mostrar infos
    4. Contar o numero de alunos de um determinado curso
    5. Imprimir professores de maior salário
    6. Sair
*/

void printa_menu()
{
    printf( "\n1. Inserir uma pessoa na lista"
            "\n2. Remover pela matricula"
            "\n3. Buscar pela matricula - caso ache, mostrar infos"
            "\n4. Contar o numero de alunos de um determinado curso"
            "\n5. Imprimir professores de maior salario"
            "\n6. Sair\n> " );
}

lista* menu(lista *l, int op)
{
    int mat;
    char curso[30];

    switch (op)
    {
        case 1:
            l=insere(l);
            break;

        case 2:
            printf("Digite a matricula: ");
            scanf("%d", &mat);
            l=Remove(l, mat);
            break;

        case 3:
            printf("Digite a matricula: ");
            scanf("%d", &mat);
            Busca(l, mat);
            break;

        case 4:
            printf("Digite a matricula: ");
            fflush(stdin);
            gets(curso);
            printf("Temos %d alunos em %s\n", conta_alunos(l, curso), curso);
            break;
        
        case 5:
            maiores_salarios(l);
            break;
        
        case 6:
            printf("Programa finalizado!");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
    }
    return l;
}

int main()
{
    lista *l = inicializa();
    int op = 0;
    while (op!=6)
    {
        printa_menu();
        scanf("%d", &op);
        l = menu(l,op);
    }
    
    libera(l);
    return 0;
}