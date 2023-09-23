#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int prioridade;
} nave;

void descer(nave *heap, int i);

void subir(nave *heap, int i);

void cria_heap(nave *heap, int tam);

void insercao(nave *heap, int tam);

void remover(nave *heap,int n);
