#include "chromosome.h"
#include <iostream>
using namespace std;
Chromosome::Chromosome(int genQty){
    this->_genQty = genQty;

    for(int i=0; i<genQty; i++){
        Genotype temp = Genotype();
        _gen.append(temp);
    }
}


int Chromosome::getGenQty(){
    return this->_genQty;
}

void Chromosome::insertGen(Genotype& gen){
    this->_gen.append(gen);
}


double Chromosome::getFitness(){
    return this->_gen.last().getValue();
}

Genotype* Chromosome::getGen(int i){
    return &this->_gen[i];
}

/*
 * Avalia a população baseado em alguma função a ser implementada.
 * TODO: Criar função baseado nos pesos do tempo, batida e distância.
 */
void Chromosome::evaluate(){
    return _gen.last().setValue(1.0);
}
