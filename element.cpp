#include "element.h"

Element::Element(){}

Element::Element(int size){
    this->_size = size;

    for(int i=0; i<size; i++)
    {
        Genotype temp;
        _gen.append(temp);
    }
}

Element::~Element(){

}

int Element::getSize(){
    return this->_size;
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
