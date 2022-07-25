#ifndef Heap_H
#define Heap_H

typedef struct heap *Heap;
Heap inicializar();
int inserir(Heap h, int key, void* x, int size);
int remover(Heap h, int *key, void* x, int size);
void print(Heap h, void f(void* info));
void destruir(Heap h);

#endif