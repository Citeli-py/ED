#include <stdio.h>
#include <stdlib.h>
#include "minheap.h"

void print_info(void* info)
{
    char *x = (char*) malloc(sizeof(char));
    x = (char*) info;
    printf("info: %c\n\n", *x);
}

int main()
{
    char *a = "matheus123";
    char b;
    int i;

    Heap h = inicializar();
    for(int i=0; i<10; i++)
        inserir(h, i, &a[i], sizeof(char));

    print(h, print_info);

    for(int i=0; i<3; i++)
    {
        remover(h, &i, &b, sizeof(char));
        printf("%c ", b);
    }
    printf("\n");

    print(h, print_info);

    destruir(h);
    return 0;
}