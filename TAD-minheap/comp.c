#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("gcc -c minheap.c -o minheap.o");
    system("gcc main.c minheap.o -o main.exe");
    return 0;
}