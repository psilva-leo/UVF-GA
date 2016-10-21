#include "element.h"

Element::Element(int genQty){
    this->_genQty = genQty;

    for(int i=0; i<genQty; i++)
    {
        Genotype temp;
        _gen.append(temp);
    }
}


int Element::getGenQty(){
    return this->_genQty;
}

void Element::setGen(Genotype& gen, int position){
    this->_gen.replace(position, gen);
}


Genotype Element::getFitness(){
    return _gen.last();
}

Genotype Element::getGen(int i){
    return _gen.takeAt(i);
}

/*
 * Avalia a população baseado em alguma função a ser implementada.
 * TODO: Criar função baseado nos pesos do tempo, batida e distância.
 */
double Element::evaluate(){
    return 1.0;
}
