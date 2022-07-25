#include <stdio.h>
#include <stdlib.h>
/*Todas as combinações de {a,e,i} de tamanho n em q n(a)>n(e)+n(i)*/

void print(char *vet, int n)
{
    for(int i=0; i<n; i++)
        printf("%c ", vet[i]);
    printf("\n");
}

int num(char *vet, char c, int n)
{
    int count=0;
    for(int i=0; i<n; i++)
        if(vet[i] == c)
            count ++;
    return count;
}

void permutacoes(char *vet, int pos, int n)
{
    char aux[3] = {'a','e','i'};
    if(pos == n)
    {
        if(num(vet,'a',n)>(num(vet,'e',n) + num(vet,'i',n)))
            print(vet, n);
    }
    else
    {
        for(int i=0;i<3;i++)
        {
            vet[pos]=aux[i];
            permutacoes(vet, pos+1, n);
        }
    }
}

void libera(char *vet, int n)
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
    char *vet = (char *) malloc(n*sizeof(char));
    permutacoes(vet,0,n);
    libera(vet, n);
    return 0;
}