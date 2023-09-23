#include "naves.h"

/*Função de descida da heap, responsável por alterar a posição da nave de acordo com a prioridade que ela possui.*/

void descer(nave *heap, int i){
        int n=5;
        int j = 2 * i;
        if (j <= n){    
            if (j < n){
                if (heap[j + 1].prioridade > heap[j].prioridade){
                    j ++;
                }
            }
            if (heap[j].prioridade > heap[i].prioridade){
                nave aux = heap[i];
                heap[i] = heap[j];
                heap[j] = aux;

                descer(heap, j);
            }
        }
}


/*Função de descida da heap, responsável por alterar a posição da nave de acordo com a prioridade que ela possui.*/
void subir(nave *heap, int i){
    int j = i/2;
    if(j>=1){
        if(heap[i].prioridade > heap[j].prioridade){
                nave aux = heap[i];
                heap[i] = heap[j];
                heap[j] = aux;
                subir(heap, j);
        }
    }
}


/*Função designada para criar a heap, depois ela já retorna ordenada baseado
na priodidade de cada um dos elementso que possuímos dentro do nosso vetor*/
void cria_heap(nave *heap, int tam){
    tam/=2;
    while(tam!=0){
        descer(heap ,tam);
        tam--;
        
    }
}


//alocação de memoria, para aumentar o tamanho da heap para adicionar nova nave
/*Função resposável por inserir uma nova nave dentro na nossa fila de priodidade,
logo após a inserção a função já posiciona o novo elemento de forma ordenada
mantendo a estrutura heap.*/
void insercao(nave *heap, int tam){
    int i= tam;
    scanf("%d", &heap[i].prioridade);
    subir(heap, i);

}

/*Função resposável por remover(passsar para outro universo) uma nave dentro na nossa fila de priodidade.
Antes de realizar a remoção, utiliza função 'verifica_prioridade para verificar se a nave deve ser realmente
a primeira na heap, se não for, a heap é reordenada e a nova nave é removida da estrutura e sai do nosso UNIVERSO.*/
void remover(nave *heap,int n){
    heap[1].prioridade = heap[n].prioridade;
    heap[n].prioridade=0;
    descer(heap, 1);
}
 
