#include "chromosome.h"

Chromosome::Chromosome(int genQty){
    this->_genQty = genQty;
    this->_fitness = 1.0;

    for(int i=0; i<genQty; i++){
        Genotype temp = Genotype(0.0, 2.0);
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
    return this->_fitness;
//    return this->_gen.last().getValue();
}

Genotype* Chromosome::getGen(int i){
    return &this->_gen[i];
}

/*
 * Avalia a população baseado em alguma função a ser implementada.
 * TODO: Criar função baseado nos pesos do tempo, batida e distância.
 */
void Chromosome::evaluate(){
    this->_fitness = 1.0;
}
