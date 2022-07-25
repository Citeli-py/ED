#include <stdio.h>

#define N 4

void inicia(int tabuleiro[N][N])
{
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            tabuleiro[i][j] = 0;
}

void printa(int tabuleiro[N][N])
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
            printf("%d ",tabuleiro[i][j]);
        printf("\n");
    }
    printf("\n");
}

int num(int m[N][N])
{
    int soma=0;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            soma += m[i][j];
    return soma;
}

int colide_reta(int r[4][2])
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            if(i!=j)
            {
                if(r[i][0] == r[j][0]) // Linha
                    return 1;
                if(r[i][1] == r[j][1]) // coluna
                    return 1;
            }
        }
    return 0;
}

int colide_diagonal(int m[N][N])
{
    int soma;

    for(int k=1; k<N+1; k++) //Direita-Esquerda
    {
        soma = 0;
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                if(j+i == k)
                {
                    soma += m[i][j];
                    if (soma>1)
                        return 1;
                }
    }
    soma=0;

    int k=0, l=0, c=N-2; // Em loop
    while(l<=N)
    {
        if(c+k>=N)
        {
            k=0;
            soma=0;
            if(c>0)
                c--;
        }

        if(l+k>=N)
        {
            k=0;
            soma=0;
            if(l<N)
                l++;
        }
        soma += m[l+k][c+k];
        printf("(%d, %d) ", l+k,c+k);
        //if(soma>1)
        //    return 1;
        k++;
    }

    return 0;
}

void encontra_rainhas(int m[N][N], int rainhas[4][2])
{
    int l=0;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(m[i][j]==1)
            {
                rainhas[l][0] = i;
                rainhas[l][1] = j;
                l++; 
            }
}

int colide(int m[N][N])
{
    // Verificar se existe colisões, anotar as posições da rainha e 
    // ver se as diagonais ou retas se encontram com a posição das rainhas
    int rainhas[4][2];
    encontra_rainhas(m, rainhas);
    return colide_diagonal(m) + colide_reta(m);
}

void backtracking(int m[N][N], int pos, int n)
{
    // i=pos%N | j=pos/N
    if(pos == n)
    {
        if(num(m)==4 && !colide(m))
            printa(m);
    }
    else
    {
        for(int i=0;i<2;i++)
        {
            m[pos/N][pos%N] = i;
            backtracking(m,pos+1,n);
        }
    }
}

int main()
{
    // 0 casa desocupada, 1 rainha
    int tab[N][N];
    inicia(tab);
    tab[1][1] = 1;
    tab[1][3] = 1;
    tab[2][2] = 1;
    tab[3][2] = 1;
    printa(tab);
    printf("%d", colide_diagonal(tab));
    //backtracking(tab,0,N*N);
    return 0;
}