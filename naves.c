#include "naves.h"

int main() {
  int quantNaves = 5;
  int escolha;
  int loop = 1;
  nave heap[1000];
  heap[1].prioridade = 7;
  heap[2].prioridade = 13;
  heap[3].prioridade = 1;
  heap[4].prioridade = 9;
  heap[5].prioridade = 40;

  cria_heap(heap, quantNaves);

  while (loop == 1) {
    printf("MENU-------------\n1 - Listar Naves;\n2 - Inserir Nave;\n3 - "
           "Passar Nave pelo portal;\n4 - encerrar;\n");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      for (int i = 1; i <= quantNaves; i++) {
        printf("%d ", heap[i].prioridade);
      }
      printf("\n");
      break;
    case 2:
      quantNaves++;
      insercao(heap, quantNaves);
      break;
    case 3:
      remover(heap, quantNaves);
      quantNaves--;
      break;
    case 4:
      loop = 0;
      break;
    default:
      break;
    }
  }
}
