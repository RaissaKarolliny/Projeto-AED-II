#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição das structs

/* Na struct passageiro temos o nome, a idade, o plneta de origem, e um
 * identificador formatado da seguinte forma: as 3 primeiras letras do planeta
 * de origem e um número que é dado pela ordem de inserção da nave na heap.
 */
typedef struct {
  char nome[50];
  int idade;
  char planeta[50];
  char id[60];
} passageiro;

/* Na struct nave temos com atributo um id(usado para verificar a priorodade da
 * nade mais adiante no código na funcão verifica()), temos um vetor de
 * passageiros(cada nave pode ter entre 1 e 3 passageiros), um valor interio que
 * representa a quantidade de passageiros na nave, a prioridade da nave, e um
 * vetor de recusos (esse vetor armazena apenas os Id's dos recursos, que são
 * representados por números primos de 2 à 13) */
typedef struct {
  int idNave;
  passageiro passageiros[3];
  int prioridade;
  int recursos[3];
} nave;

/* Na struct heap temos um vetor verificaro, ele armazena as prioridades das
 * naves para a verificação das mesmas, temos um inteiro que representa a
 * quantidade de naves armazenadas na nossa heap */
typedef struct {
  int verificador[1000];
  int tamanhoHeap;
  nave heap[1000];
} heap;

typedef struct {
  int quantidadeElementos;
  nave elementoHash[6];
} vaga;

typedef struct {
  vaga linha[20];
} hash;

// Assinaturas das funções
void subir(heap *naves, int i);

void listar(heap *naves);

void insercao(heap *naves);

void descer(heap *naves, int i);

void cria_heap(heap *naves);

void preencher(heap *naves);

void remover(heap *naves, hash *hash);

void dezPorcento(heap *naves);

void verifica(heap *naves);

void inserirHash(heap *naves, hash *hash);

void csv(heap *naves);

void listarHash(hash *hash);

void aberturas(hash *hash);

void listaPrioridade(heap *naves);
