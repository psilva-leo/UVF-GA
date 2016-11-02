#include "chromosome.h"

Chromosome::Chromosome(int genQty){
    this->_genQty = genQty;

    for(int i=0; i<genQty; i++)
    {
        Genotype temp;
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
    return _gen.last().getValue();
}

Genotype Chromosome::getGen(int i){
    return _gen.takeAt(i);
}

/*
 * Avalia a população baseado em alguma função a ser implementada.
 * TODO: Criar função baseado nos pesos do tempo, batida e distância.
 */
double Chromosome::evaluate(){
    return 1.0;
}
