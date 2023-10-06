#include "header.h"

int main() {
  setlocale(LC_ALL, "Portuguese");
  // Declaraçãoo das variáveis de controle para o menu

  /* A varivÃ¡vel escolha recebe a opção dada pelo usuário, a variável
   * loop serve de controle para manter o menu reapaarecendo, a declaração
   * do ponteiro naves */
  int escolha;
  int loop = 1;
  heap p;
  heap *naves;
  naves = &p;
  naves->tamanhoHeap = 5;

  hash h;
  hash *hash;
  hash = &h;

  preencher(naves);
  // csv(naves);
  cria_heap(naves);

  while (loop == 1) {
    printf("MENU-------------\n1 - Listar Naves;\n2 - Inserir Nave;\n3 - "
           "Passar Nave pelo portal;\n4 - Listar hash;\n5 - Próximas aberturas "
           "do portal;\n0 - Encerrar\n");
    scanf("%d", &escolha);
    switch (escolha) {
    case 1:
      listar(naves);
      break;
    case 2:
      insercao(naves);
      break;
    case 3:
      remover(naves, hash);
      break;
    case 4:
      listarHash(hash);
      break;
    case 5:
      aberturas(hash);
      break;
    case 0:
      loop = 0;
    default:
      break;
    }
  }
}