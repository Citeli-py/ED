#include "abb.h"
#include<stdio.h>
#include<stdlib.h>

void menu()
{
    printf( "\n\n1- Ler uma arvore de um arquivo\n"
            "2- Imprimir a arvore (pre-ordem, em-ordem, pos-ordem e em largura)\n"
            "3- Verificar se um elemento x existe\n"
            "4- Imprimir o nivel de um no x\n"
            "5- Imprimir as folhas menores que um valor x\n"
            "6- Inserir um no x na arvore\n"
            "7- Remover um no x da arvore\n"
            "8- Sair\n"
            "|Escolha> ");
}

int main()
{
    arvore *a;
    FILE *f;
    int op=0, aux;
    char arquivo[30];

    while (op != 8)
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
                printf("Qual elemento: ");
                scanf("%d", &aux);
                NivelNo(a, aux, 0);
                break;

            case 5:
                printf("Qual elemento: ");
                scanf("%d", &aux);
                printf("Folhas menores que %d: ", aux);
                Folhas(a, aux);
                break;

            case 6:
                printf("Insira um valor: ");
                scanf("%d", &aux);
                a = inserir(a, aux);
                break;
            
            case 7:
                printf("Remover qual elemento: ");
                scanf("%d", &aux);
                a = remover(a, aux);
                break;

            case 8:
                break;

            default:
                op = 0;
                printf("Entrada invalida!");
                break;
        }
    }
    fclose(f);
    libera_arvore(a);
    printf("\nPrograma Finalizado!\n");
    return 0;
}
