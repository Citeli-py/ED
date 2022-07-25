#include <stdio.h>
#include <stdlib.h>
/*Dado um valor em centavos, imprimir todas as combinações
com moedas de 1,5,10,25 e 50 */

void print(int *vet, int n)
{
    printf("\n");
    int aux[5] = {1,5,10,25,50};
    for(int i=0; i<n; i++)
        if(vet[i] > 0)
            printf("%d moedas de %d centavos\n", vet[i], aux[i]);
    printf("=======================\n");
}

int soma(int *vet, int n)
{
    int soma=0;
    int aux[5] = {1,5,10,25,50};

    for(int i=0;i<n;i++)
        soma+= vet[i]*aux[i];
    return soma;
}

void permutacoes(int *vet, int pos, int n, int valor)
{
    if(pos == n)
    {
        if(soma(vet,n) == valor)
            print(vet, n);
    }
    else
    {
        for(int i=0;i<=valor;i++)
        {
            vet[pos]=i;
            permutacoes(vet, pos+1, n, valor);
        }
    }
}

void libera(int *vet, int n)
{
    for(int i=1; i<n; i++)
        free(vet[i]);
    free(vet[0]);
}

int main()
{
    int valor, n=5;
    printf("Digite o valor em centavos: ");
    scanf("%d", &valor);
    int *vet = (int *) malloc(n*sizeof(int));
    permutacoes(vet,0,n,valor);
    libera(vet, n);
    return 0;
}