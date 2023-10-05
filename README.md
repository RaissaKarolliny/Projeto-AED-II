# HEAP
Projeto de implementação AED II.
Nosso projeto contém 3 arquivos, são eles: Functions.c, Header.h e Main.c. 
No arquivo Header definimos as structs, são elas: Nave, que contém os passageiros, os recursos a prioridade e um id; 
Heap, com um vetor verificador, um vetor de heaps e uma variável para o tamanho; Vaga, com um vetor de elemetos hash e uma variável para o tamanho;
E Hash, com um vetor de linhas da hash. Além disso, temos as assinaturas de todas as funções criadas no arquivo Function.

No arquivo Function temos a implementação de uma heap e uma tabela hash, com criação, inserção e 
remoção de elementos nas mesmas. Há também funções para verificar a prioridade das naves, listar as naves e a tabela e uma função para trocar a prioridade em 10% das vezes.

No arquivo Main criamos a heap e um ponteiro para ela, o mesmo foi feito para hash, nela chamamos a função para criar a heap e passamos como parâmetro o ponteiro de naves.
com um switch case criamos um menu para que o usuário possa escolher qual operação deseja realizar, nele disponibilizamos a inserção de nave,
a passagem de naves pelo portal, estado atual da heap, estado atual da hash e também das próximas aberturas do portal.


