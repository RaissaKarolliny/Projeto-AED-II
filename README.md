# HEAP
Projeto de implementação AED II.
Primeiramente é importante destacar um pouco da lógica por trás das estruturas heap e hash que criamos.
A nossa heap é uma struct que possui um vetor de elementos naves, esse vetor será nossa heap propriamente dita.
Na nossa hash, temos uma lógica um pouco mais complicada, na struct hash, temos um campo que consiste em um vetor
ele possui 20 posições(total de permutações com 6 elementos), ele armazena elementos do tipo vaga, esse elemento,
por si só, tem um campo que armazena as permutações de cada combinação de 3 elementos, criando assim, uma matriz de proporção
20x6.


Em uma galáxia distante, um grupo de diversos sistemas solares em uma região da galáxia começou a instaurar uma
revolução para tomar o controle das decisões de comando por meio da opressão aos opositores. Muitos planetas foram
dizimados ou escravizados em caso de recusa a se submeter ao novo sistema. Um grupo de pesquisadores de um sistema
planetário próxima a borda da galáxia descobriu uma forma de criar uma conexão direta entre a galaxia e a Via Láctea,
através de um passagem que suporta o tamanho de apenas uma nave espacial por vez. Com isso, todos aqueles sistemas
que desejam fugir para a Via Láctea devem passar pela passagem recém descoberta. Infelizmente os recursos para criar
uma passagem é conhecido existir apenas nesta região da galáxia. Iniciou-se então uma longa migração de toda a galáxia
para esta região em busca de conseguir exílio do sistema opressor, levando a um acúmulo de espaçonaves que desejam
utilizar a passagem. Um sistema de controle de uso da passagem deve ser criado para que espaçonaves transportando
recursos raros, recursos indispensáveis à vida de diferentes espécies, indivíduos que necessitem de tratamento especial, e
assim por diante, tenham maior prioridade para uso da passagem.

Nosso projeto contém 3 arquivos, são eles: Functions.c, Header.h e Main.c. 
No arquivo Header definimos as structs, são elas: Nave, que contém os passageiros, os recursos a prioridade e um id; 
Heap, com um vetor verificador, um vetor de heaps e uma variável para o tamanho; Vaga, com um vetor de elemetos hash e uma variável para o tamanho;
E Hash, com um vetor de linhas da hash. Além disso, temos as assinaturas de todas as funções criadas no arquivo Function.

No arquivo Function temos a implementação de uma heap e uma tabela hash, com criação, inserção e 
remoção de elementos nas mesmas. Há também funções para verificar a prioridade das naves, listar as naves e a tabela, e uma função para trocar a prioridade em 10% das vezes.

No arquivo Main criamos a heap e um ponteiro para ela, o mesmo foi feito para hash, Chamamos a função para criar a heap e passamos como parâmetro o ponteiro de naves.
Com um switch case criamos um menu para que o usuário possa escolher qual operação deseja realizar, nele disponibilizamos a inserção de nave,
a passagem de naves pelo portal, estado atual da heap, estado atual da hash e também das próximas aberturas do portal.

Trabalho realizado por:
Pedro Henrique Bezerra Simeão;
Raissa Karoliny Da Silva Rodrigues.


