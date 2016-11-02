#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <UVF-GA/geneticalgorithm/population.h>
#include <time.h>
#include <QList>

#define POPSIZE 10

int main(int argc, char *argv[]){
//    //if(argc < 2){return -1;}
//    //Population P = new Population(argv[1]);

    Population P = Population(POPSIZE);

    srand(time(NULL));

    P.generate();
    P.print();
    QList<Population> pop;
    pop.append(P);
    P.selection(pop);

    //P->print();

//    seleciona(inicial) => selecionados (x elementos)

//    crossover(selecionados) => pop_atual1

//    mutação(pop_atual1)   => pop_atual2

//    evaluation()

//    seleciona(selecionados, pop_atual2) (x elementos)


    return 0;
}
