#include "element.h"

Element::Element(int size){
    this->size = size;

    for(int i=0; i<size; i++)
    {
        Genotype temp = new Genotype(1.0, 0.0);
        genotypes.append(0.0);
    }
}

double Element::getFitness(){
    return gen.last();
}

/*
 * Avalia a população baseado em alguma função a ser implementada.
 * TODO: Criar função baseado nos pesos do tempo, batida e distância.
 */
double Element::evaluate(){
    return 1.0;
}
