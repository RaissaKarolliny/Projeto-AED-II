#include "header.h"
/*Função de subida da heap, responsável por alterar a posição da nave de
 * acordo com a prioridade que ela possui.*/
void subir(heap *naves, int i) {
  int j = i/2;
  if (j >= 1) {
    if (naves->heap[i].prioridade > naves->heap[j].prioridade) {
      nave aux = naves->heap[i];
      naves->heap[i] = naves->heap[j];
      naves->heap[j] = aux;
      subir(naves, j);
    }
  }
}

/* A função dezPorcento é responsável por atribuir uma prioridade aleatória
 * para 10% das naves inseridas na nossa fila de prioridades */
void dezPorcento(heap *naves) {
  srand(time(NULL));
  if ((rand() % 10) == 5) {
    naves->heap[naves->tamanhoHeap].prioridade = (1 + rand() % 100);
  }
}

/* Essa função recebe os valos do novo elemento inserio na nossa fila, ela
 * aplica a função dezPorcendo, que em cada 10% dos casos troca a prioridade
 * da nave para um valor aleatório, ao fim da coleta de dados, aplicamos a
 * subida na nova nave */

void insercao(heap *naves) {
  system("cls");
  naves->tamanhoHeap++;
  printf("Informe a prioridade da nave:\n");
  scanf("%d", &naves->heap[naves->tamanhoHeap].prioridade);
  naves->heap[naves->tamanhoHeap].idNave = naves->tamanhoHeap;
  naves->verificador[naves->tamanhoHeap] =
      naves->heap[naves->tamanhoHeap].prioridade;
  dezPorcento(naves);
  for (int i = 0; i < 3; i++) {
    printf("Informe o primeiro nome do passageiro %d\n", i + 1);
    scanf("%s", naves->heap[naves->tamanhoHeap].passageiros[i].nome);

    printf("Informe o planeta de origem do passageiro %d\n", i + 1);
    scanf("%s", naves->heap[naves->tamanhoHeap].passageiros[i].planeta);

    printf("Informe o id do passageiro %d\n", i + 1);
    scanf("%s", naves->heap[naves->tamanhoHeap].passageiros[i].id);

    printf("Informe a idade do passageiro %d\n", i + 1);
    scanf("%d", &naves->heap[naves->tamanhoHeap].passageiros[i].idade);
  }
  printf("Informe o id dos recursos transportados na nave(devem ser "
         "distintos):\n");
  scanf("%d", &naves->heap[naves->tamanhoHeap].recursos[0]);
  scanf("%d", &naves->heap[naves->tamanhoHeap].recursos[1]);
  scanf("%d", &naves->heap[naves->tamanhoHeap].recursos[2]);
  subir(naves, naves->tamanhoHeap);
}

/*Função de descida da heap, responsável por alterar a posição da nave de
 * acordo com a prioridade que ela possui.*/
void descer(heap *naves, int i) {
  int j = 2 * i;
  if (j <= naves->tamanhoHeap) {
    if (j < naves->tamanhoHeap) {
      if (naves->heap[j + 1].prioridade > naves->heap[j].prioridade) {
        j++;
      }
    }
    if (naves->heap[j].prioridade > naves->heap[i].prioridade) {
      nave aux = naves->heap[i];
      naves->heap[i] = naves->heap[j];
      naves->heap[j] = aux;
      descer(naves, j);
    }
  }
}

/* A função verifica funciona da seguinte maneira: Quando uma nave é inserida
 * na nossa fila, ela recebe um id de verificação, ele funciona como o indice
 * pra o vetor verificador, que armazena a prioridade verdadeira da nave, esse
 * id é equivalente a ordem de inserção do elemento na heap, em caso da nave
 * estar com uma prioridade errada, aplicamos descer à ela (precisamos desse
 * mescanismo uma vez que e10% das naves tem uma prioridade trocada)*/
void verifica(heap *naves) {
  if (naves->heap[1].prioridade != naves->verificador[naves->heap[1].idNave]) {
    naves->heap[1].prioridade = naves->verificador[naves->heap[1].idNave];
    descer(naves, 1);
  }
}

/*Função designada para criar a heap, depois ela já retorna ordenada baseado
 * na priodidade de cada um dos elementso que possuímos dentro do nosso vetor*/
void cria_heap(heap *naves) {
  int tamanhoHeap = naves->tamanhoHeap;
  for (tamanhoHeap /= 2; tamanhoHeap != 0; tamanhoHeap--) {
    descer(naves, tamanhoHeap);
  }
}

void listarHash(hash *hash) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < hash->linha[i].quantidadeElementos; j++) {
      printf("[%d][%d] = %d ", i, j, hash->linha[i].elementoHash[j].prioridade);
    }
    printf("\n");
  }
}

/* função para inserir na hash, recebemos um ponteiro para as naves e a hash.
 * vericamos em qual linha da hash a nave deve ser inserida de acordo com o
 * resultado da multiplicação dos índices dos recursos,depois verificamos se a
 * permutação de recursos da nave já está na nossa linha da hash, em caso
 * negativo o elemento é inserido e a quantidade de elementos é imcrementada em
 * + 1. Ao alcançarmos 6 elementos teremos as 6 permutações possiveis, e então
 * zeramos a quantidade de elementos e realizamos 6 remoções na nossa heap.  */

void inserirHash(heap *naves, hash *hash) {
  int linha = naves->heap[1].recursos[0] * naves->heap[1].recursos[1] *
              naves->heap[1].recursos[2];
  int verificador = 0;
  switch (linha) {
  case 30:
    for (int i = 0; i < hash->linha[0].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[0].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[0].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[0].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[0].elementoHash[verificador] = naves->heap[1];
    hash->linha[0].quantidadeElementos++;
    if (hash->linha[0].quantidadeElementos == 6) {
      // AUMENTA PORTA
      hash->linha[0].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 42:
    for (int i = 0; i < hash->linha[1].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[1].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[1].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[1].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[1].elementoHash[verificador] = naves->heap[1];
    hash->linha[1].quantidadeElementos++;
    if (hash->linha[1].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[1].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 66:
    for (int i = 0; i < hash->linha[2].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[2].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[2].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[2].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[2].elementoHash[verificador] = naves->heap[1];
    hash->linha[2].quantidadeElementos++;
    if (hash->linha[2].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[2].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }

    break;
  case 78:
    for (int i = 0; i < hash->linha[3].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[3].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[3].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[3].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[3].elementoHash[verificador] = naves->heap[1];
    hash->linha[3].quantidadeElementos++;
    if (hash->linha[3].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[3].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 70:
    for (int i = 0; i < hash->linha[4].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[4].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[4].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[4].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[4].elementoHash[verificador] = naves->heap[1];
    hash->linha[4].quantidadeElementos++;
    if (hash->linha[4].quantidadeElementos == 6) {
      hash->linha[4].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 110:
    for (int i = 0; i < hash->linha[5].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[5].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[5].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[5].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[5].elementoHash[verificador] = naves->heap[1];
    hash->linha[5].quantidadeElementos++;
    if (hash->linha[5].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[5].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 130:
    for (int i = 0; i < hash->linha[6].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[6].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[6].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[6].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[6].elementoHash[verificador] = naves->heap[1];
    hash->linha[6].quantidadeElementos++;
    if (hash->linha[6].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[6].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 154:
    for (int i = 0; i < hash->linha[7].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[7].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[7].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[7].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[7].elementoHash[verificador] = naves->heap[1];
    hash->linha[7].quantidadeElementos++;
    if (hash->linha[7].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[7].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 182:
    for (int i = 0; i < hash->linha[8].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[8].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[8].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[8].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[8].elementoHash[verificador] = naves->heap[1];
    hash->linha[8].quantidadeElementos++;
    if (hash->linha[8].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[8].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 286:
    for (int i = 0; i < hash->linha[9].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[9].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[9].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[9].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[9].elementoHash[verificador] = naves->heap[1];
    hash->linha[9].quantidadeElementos++;
    if (hash->linha[9].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[9].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 105:
    for (int i = 0; i < hash->linha[10].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[10].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[10].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[10].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[10].elementoHash[verificador] = naves->heap[1];
    hash->linha[10].quantidadeElementos++;
    if (hash->linha[10].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[10].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 165:
    for (int i = 0; i < hash->linha[11].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[11].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[11].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[11].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[11].elementoHash[verificador] = naves->heap[1];
    hash->linha[11].quantidadeElementos++;
    if (hash->linha[11].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[11].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 195:
    for (int i = 0; i < hash->linha[12].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[12].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[12].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[12].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[12].elementoHash[verificador] = naves->heap[1];
    hash->linha[12].quantidadeElementos++;
    if (hash->linha[12].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[12].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 231:
    for (int i = 0; i < hash->linha[13].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[13].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[13].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[13].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[13].elementoHash[verificador] = naves->heap[1];
    hash->linha[13].quantidadeElementos++;
    if (hash->linha[13].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[13].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 273:
    for (int i = 0; i < hash->linha[14].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[14].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[14].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[14].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[14].elementoHash[verificador] = naves->heap[1];
    hash->linha[14].quantidadeElementos++;
    if (hash->linha[14].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[14].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 429:
    for (int i = 0; i < hash->linha[15].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[15].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[15].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[15].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[15].elementoHash[verificador] = naves->heap[1];
    hash->linha[15].quantidadeElementos++;
    if (hash->linha[15].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[15].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 385:
    for (int i = 0; i < hash->linha[16].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[16].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[16].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[16].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[16].elementoHash[verificador] = naves->heap[1];
    hash->linha[16].quantidadeElementos++;
    if (hash->linha[16].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[16].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 455:
    for (int i = 0; i < hash->linha[17].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[17].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[17].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[17].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[17].elementoHash[verificador] = naves->heap[1];
    hash->linha[17].quantidadeElementos++;
    if (hash->linha[17].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[17].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 715:
    for (int i = 0; i < hash->linha[18].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[18].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[18].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[18].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[18].elementoHash[verificador] = naves->heap[1];
    hash->linha[18].quantidadeElementos++;
    if (hash->linha[18].quantidadeElementos == 6) {
      // AUMENTA PORTAL
      hash->linha[18].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  case 1001:
    for (int i = 0; i < hash->linha[19].quantidadeElementos; i++) {
      if ((naves->heap[1].recursos[0] ==
           hash->linha[19].elementoHash[i].recursos[0]) &&
          (naves->heap[1].recursos[1] ==
           hash->linha[19].elementoHash[i].recursos[1]) &&
          (naves->heap[1].recursos[2] ==
           hash->linha[19].elementoHash[i].recursos[2])) {
        return;
      } else {
        verificador++;
      }
    }
    hash->linha[19].elementoHash[verificador] = naves->heap[1];
    hash->linha[19].quantidadeElementos++;
    if (hash->linha[19].quantidadeElementos == 6) {
      // AuMENTA PORTAL
      hash->linha[19].quantidadeElementos = 0;
      for (int i = 0; i < 6; i++) {
        remover(naves, hash);
      }
    }
    break;
  default:
    break;
  }
}

/* A função aberturas() é uma função desiganda para verificar quantas
 * permitações de recursos faltam para o nosso portal ser aberto e realizar
 * várias remoções.*/
void aberturas(hash *hash) {
  system("cls");
  for (int i = 0; i < 20; i++) {
    printf("A Linha[%d] tem [%d] Permutações restantes\n", i,
           6 - hash->linha[i].quantidadeElementos);
  }
}
/* Função de remoção resposável por "Passar a nave para o novo
 * universo", ele verifica se a heap essá vazia, se não estiver realiza um
 * verificação analisando a prioridade, depois realiza a remoção,
 * sobrepondo o primeiro elemento com o último e removendo o último
 * elemento da fila */
void remover(heap *naves, hash *hash) {
  system("cls");
  if (naves->tamanhoHeap != 0) {
    verifica(naves);
    inserirHash(naves, hash);
    naves->heap[1] = naves->heap[naves->tamanhoHeap];
    naves->heap[naves->tamanhoHeap].prioridade = 0;
    descer(naves, 1);
    naves->tamanhoHeap--;
  }
}

/* Função que lista todas as naves dentro da heap, printando todos so
 * atrubitos relevantes */
void listar(heap *naves) {
  system("cls");
  for (int i = 1; i <= naves->tamanhoHeap; i++) {
    printf("Prioridade da nave (%d) -------- [%d]\n", i,
           naves->heap[i].prioridade);
    printf("ID dos recursos transportados[%d|%d|%d]\n",
           naves->heap[i].recursos[0], naves->heap[i].recursos[1],
           naves->heap[i].recursos[2]);
    printf("ID da nave [%d]\n\n", naves->heap[i].idNave);
    for (int j = 0; j < 3; j++) {
      printf(" Nome: %s\n Idade: %d\n Id: %s\n Planeta: %s\n\n",
             naves->heap[i].passageiros[j].nome,
             naves->heap[i].passageiros[j].idade,
             naves->heap[i].passageiros[j].id,
             naves->heap[i].passageiros[j].planeta);
    }
  }
  printf("\n");
}
void listaPrioridade(heap *naves){
    for(int i=1;i<=naves->tamanhoHeap; i++){
        printf("[%d] ", naves->heap[i].prioridade);
    }
}



void csv(heap *naves) {
  char box[600];
  FILE *file;
  char *ponteiroControle;
  int contadorLinhas = 1;
  file = fopen("dados.csv", "r");
  while (EOF != fscanf(file, "%[^\n]\n", box)) {
    ponteiroControle = strtok(box, ",");
    int contadorColunas = 0;
    if (ponteiroControle == NULL) {
      printf("ERRO");
    }
    while (ponteiroControle != NULL) {
      switch (contadorColunas) {
      case 0:
        naves->heap[contadorLinhas].idNave = contadorLinhas;
        naves->heap[contadorLinhas].prioridade = atoi(ponteiroControle);
        naves->verificador[contadorLinhas] = atoi(ponteiroControle);
      case 1:
        naves->heap[contadorLinhas].recursos[0] = atoi(ponteiroControle);

      case 2:
        naves->heap[contadorLinhas].recursos[1] = atoi(ponteiroControle);

      case 3:
        naves->heap[contadorLinhas].recursos[2] = atoi(ponteiroControle);

      case 4:
        strcpy(naves->heap[contadorLinhas].passageiros[0].nome,
               ponteiroControle);

      case 5:
        strcpy(naves->heap[contadorLinhas].passageiros[1].nome,
               ponteiroControle);

      case 6:
        strcpy(naves->heap[contadorLinhas].passageiros[2].nome,
               ponteiroControle);

      case 7:
        strcpy(naves->heap[contadorLinhas].passageiros[0].planeta,
               ponteiroControle);

      case 8:
        strcpy(naves->heap[contadorLinhas].passageiros[1].planeta,
               ponteiroControle);

      case 9:
        strcpy(naves->heap[contadorLinhas].passageiros[2].planeta,
               ponteiroControle);

      case 10:
        strcpy(naves->heap[contadorLinhas].passageiros[0].id, ponteiroControle);

      case 11:
        strcpy(naves->heap[contadorLinhas].passageiros[1].id, ponteiroControle);

      case 12:
        strcpy(naves->heap[contadorLinhas].passageiros[2].id, ponteiroControle);

      case 13:
        naves->heap[contadorLinhas].passageiros[0].idade =
            atoi(ponteiroControle);

      case 14:
        naves->heap[contadorLinhas].passageiros[1].idade =
            atoi(ponteiroControle);

      case 15:
        naves->heap[contadorLinhas].passageiros[2].idade =
            atoi(ponteiroControle);
      }
      contadorColunas++;
      ponteiroControle = strtok(NULL, ",");
    }
    contadorLinhas++;
    naves->tamanhoHeap = contadorLinhas - 1;
  }
  fclose(file);
  ponteiroControle = NULL;
}
