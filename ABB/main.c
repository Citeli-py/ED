#include "abb.h"
#include<stdio.h>
#include<stdlib.h>

void menu()
{
    printf( "\n\n1- Ler uma arvore de um arquivo\n"
            "2- Imprimir a arvore (pre-ordem, em-ordem, pos-ordem e em largura)\n"
            "3- Verificar se um elemento x existe\n"
            "4- Contar o numero de elementos na arvore\n"
            "5- Imprimir os nos folhas\n"
            "6- Verificar se uma arvore esta balanceada\n"
            "7- Verificar se uma arvore eh cheia\n"
            "8- Imprimir o nivel de um no\n"
            "9- Sair\n"
            "|Escolha> ");
}

int main()
{
    arvore *a;
    FILE *f;
    int op=0, aux;
    char arquivo[30];

    while (op != 9)
    {
        menu();
        scanf("%d", &op);
        switch (op)
        {
            case 1:
                printf("Nome do arquivo: ");
                scanf("%s", arquivo);
                f = fopen(arquivo, "rt");
                a = LerArvore(f);
                break;

            case 2:
                Imprimir(a);
                break;

            case 3:
                printf("Qual elemento: ");
                scanf("%d", &aux);
                if(Existe(a,aux))
                    printf("%d existe!", aux);
                else
                    printf("%d nao existe!", aux);
                break;
            
            case 4:
                aux = ContarNos(a);
                printf("A arvore tem %d nos", aux);
                break;

            case 5:
                printf("Folhas: ");
                Folhas(a);
                break;

            case 6:
                if(Balanceada(a))
                    printf("A arvore eh balanceada!");
                else
                    printf("A arvore nao eh balanceada!");
                break;
            
            case 7:
                if(Cheia(a))
                    printf("A arvore eh cheia!");
                else
                    printf("A arvore nao eh cheia!");
                break;

            case 8:
                printf("Digite o no: ");
                scanf("%d", &aux);
                NivelNo(a, aux, 0);
                break;
            
            case 9:
                break;

            default:
                op = 0;
                break;
        }
    }
    fclose(f);
    libera_arvore(a);
    return 0;
}