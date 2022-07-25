#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int totalElementos=0;

int indiceFilhoEsq(int x)
{
    int indice = (2*x) + 1;
    if(x>=totalElementos || indice>= totalElementos)
        return -1;
    else
        return indice;
}

int indiceFilhoDir(int x)
{
    int indice = (2*x) + 2;
    if(x>=totalElementos || indice>= totalElementos)
        return -1;
    return indice;
} 

int indicePai(int x)
{
    int indice = (int) floor((x-1)/2);
    if(x<=0 || x>= totalElementos)
        return -1;
    return indice;
}

void AjustarSubindo(int *heap, int pos)
{
    if(pos!=-1)
    {
        int pai = indicePai(pos);
        if(pai != -1)
        {
            if(heap[pos]<heap[pai])
            {
                int aux = heap[pos];
                heap[pos] = heap[pai];
                heap[pai] = aux;
                AjustarSubindo(heap, pai);
            }
        }
    }
}

void inserir(int *heap, int x)
{
    heap[totalElementos] = x;
    totalElementos ++;
    AjustarSubindo(heap, totalElementos-1);
}

void AjustarDescendo(int *heap, int pos)
{
    if(pos != -1 && indiceFilhoEsq(pos) != -1)
    {
        int indiceMaiorFilho = indiceFilhoEsq(pos);
        if(indiceFilhoDir(pos) != -1 && heap[indiceFilhoDir(pos)]<heap[indiceMaiorFilho])
            indiceMaiorFilho = indiceFilhoDir(pos);
            
        if(heap[indiceMaiorFilho]<heap[pos])
        {
            int aux = heap[pos];
            heap[pos] = heap[indiceMaiorFilho];
            heap[indiceMaiorFilho] = aux;
            AjustarDescendo(heap, indiceMaiorFilho);
        }
    }
}

int remover(int *heap)
{
    if(totalElementos==0)
        return -1;
    
    int retorno = heap[0];
    heap[0] = heap[totalElementos-1];
    totalElementos --;
    AjustarDescendo(heap, 0);
    return retorno;
}

void print(int *heap)
{
    printf("\n");
    for(int i=0; i<totalElementos; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

void menu(int *heap)
{
    int op=0, aux;

    while(op != 4)
    {
        printf("\n==MINHEAP==\n");
        printf("1- Inserir um elemento\n2- Remover um elemento\n3- Imprimir heap\n4- Sair\n");
        scanf("%d", &op);
        switch (op)
        {
            case 1:
                printf("Qual numero deseja inserir? ");
                scanf("%d", &aux);
                inserir(heap, aux);
                break;
            
            case 2:
                aux = remover(heap);
                if(aux != -1)
                    printf("%d foi removido!\n", aux);
                else
                    printf("Lista vazia!\n");
                break;

            case 3:
                print(heap);
                break;
            
            case 4:
                break;

            default:
                printf("Opcao errada, tente novamente\n");
                break;
        }
    }
}

int main()
{
    int heap[100];
    //menu(heap);
    for(int i=10; i>=0; i--)
        inserir(heap, i);
    print(heap);
    printf("\nPrograma finalizado!"); 
}