#include <stdio.h>

int soma(int *v)
{
    int s=0;
    for(int i=0; i<6; i++)
        s+= v[i];
    
    return s;
}

void printa(int *v)
{
    printf("Vetor: ");
    for(int i=0; i<6; i++)
        printf("%d ", v[i]);
}

void combinacoes(int *v, int pos, int x, int *cont)
{
    int v_aux[6] = {1, 7, 21, 33, 75, 81};
    if(pos == 6)
    {
        if(soma(v)==x)
        {
            *cont+=1;
            printa(v);
        }
    }
    else
    {
        for(int i=0; i<6; i++)
        {
            v[pos] = v_aux[i];
            combinacoes(v, pos+1, x, cont);
        }
    }
}

int main()
{
    int v[6];
    int i=0;
    combinacoes(v, 0, 218, &i);
    printf("\n%d", i);
    return 0;
}