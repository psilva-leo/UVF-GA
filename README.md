# Univector Field Navigation parameters optimization using Genetic Algorithm

### Grupo
 - Guilherme Caixeta de Oliveira
 - Leonardo Claudio de Paula e Silva
 - Lucas dos Santos Luchiari
 - Anderson Hiroshi
 - Franco Saraiva

### Modo de uso
```
TODO

### Modificação dos parâmetros

No arquivo myEA.h tem todos as expecificações dos parâmetros utilizados:
 - **MAX_CYCLES**            : Define a quantidade de Iterações do Algoritmo.
 - **MAX_POPULATION**        : Define o número de indivíduos da população.
 - **MAX_SELECTED**          : Define o Número de indivíduos selecionados.
 - **MUTATION_FACTOR**       : Define o fator de mutação (Quanto maior, mais lento para convergir)
 - **DATA_TYPE**             : Define o tipo de dado utilizado no Algoritmo
 - **DATA_TYPE_MIN**         : Define uma constante do menor valor disponível para o tipo de dado utilizado
 - **DATA_TYPE_MAX**         : Define uma constante do maior valor disponível para o tipo de dado utilizado
 - **DEBUG**                 : Define se serão mostrados dados de debug com todos os passos do algoritmo
 - **PARAM_QTY**             : Define a quantidade de parâmetros que possui a fução objetivo

### Modificação da função objetivo

1) Mudar a quantidade de parâmetros na flag PARAM_QTY
2) Mudar a lista de valores limites para cada parâmetro na main.c no vetor "paramLimits". Adicionar ou remover os valores;
3) Escrever a função no método "evalPopulation". ``P->dot[i][x]`` onde x é o parâmetro definido em ordem.

obs: Na função possui um comentário com exemplo de funções.

### Avaliação do resultado
Segue o exemplo de uma possível resposta:

P[0]    ( 0.981830 ) = 1.533865   
P[1]    ( -0.785930 ) = 1.752629  
P[2]    ( -1.556420 ) = -0.404106  
P[3]    ( -1.053050 ) = 0.138462  
P[4]    ( 0.249320 ) = 1.052856  
Selection: [1][0][4][3][2]  

O vetor Selection indica os indivídous com melhor função fitness em ordem. Neste exemplo a ordem é "1, 0, 4, 3, 2".
Sendo assim, o indivídou 1 é o com melhor função fitness e o indivíduo 2 o pior (dentre os selecionados).
Para achar o valor dos parâetros basta olhar na linha correspondente ao ID. Neste exemplo para achar a correspondência
do indivíduo 1 basta olhar a linha "P[1]    ( -0.785930 ) = 1.752629". O valor "-0.785930" mostra o valor encontrado
da variável. Já o valor "1.752629" indica o resultado da função fitness daquele indivíduo.
