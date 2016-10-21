#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <population.h>
#include <time.h>

int main(int argc, char *argv[]){
//    //if(argc < 2){return -1;}
//    //Population P = new Population(argv[1]);
    Population *P = new Population(10);

    srand(time(NULL));

    P->generate();

    //P->print();

//    seleciona(inicial) => selecionados (x elementos)

//    crossover(selecionados) => pop_atual1

//    mutação(pop_atual1)   => pop_atual2

//    evaluation()

//    seleciona(selecionados, pop_atual2) (x elementos)


    delete P;
    return 0;
}
