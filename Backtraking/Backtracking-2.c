#include <stdio.h>
#include <stdlib.h>
/* Todas as combinações de {15,31,55,44} de tamanho n em q soma%2 == q */

void print(int *vet, int n)
{
    for(int i=0; i<n; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

int soma(int *vet, int n)
{
    int soma=0;

    for(int i=0;i<n;i++)
        soma+= vet[i];
    return soma;
}

void permutacoes(int *vet, int pos, int n)
{
    int aux[4] = {15, 31, 55, 44};
    if(pos == n)
    {
        if(soma(vet,n)%2==0)
            print(vet, n);
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            vet[pos]=aux[i];
            permutacoes(vet, pos+1, n);
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
    int n;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    int *vet = (int *) malloc(n*sizeof(int));
    permutacoes(vet,0,n);
    libera(vet, n);
    return 0;
}