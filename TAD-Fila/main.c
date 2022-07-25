#include "fila.h"
#include <stdio.h>

/*
1. inserir
2. Remover (imprima o removido)
3. imprimir
4. sair
*/

int menu(Fila f)
{
    int op, aux;
    printf( "1. inserir\n"
            "2. Remover\n"
            "3. imprimir\n"
            "4. sair\n> ");

    scanf("%d", &op);
    switch (op)
    {
    case 1:
        printf("Insira um numero: ");
        scanf("%d", &aux);
        if(add(f, aux))
            printf("\n%d adicionado!\n\n", aux);
        else
            printf("\nLista cheia!\n\n");

        break;

    case 2:
        if(rmv(f,&aux))
            printf("\n%d removido!\n\n", aux);
        else
            printf("\nLista vazia!\n\n");
        break;

    case 3:
        imprimir(f);
        break;

    case 4:
        printf("\nPrograma finalizado!\n");
        break;
    
    default:
        break;
    }
    return op;
}

int main()
{
    Fila f;
    int op=0;
    f = inicializa();
    while (op != 4)
        op = menu(f);
    
    libera(f);
    return 0;
}