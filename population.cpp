#include "population.h"

Population::Population(int size){
    for(int i=0; i>size; i++){
        Element temp = Element();
        pop.append(temp);
    }
}

Element Population::getElement(int index){
    return pop.at(index);
}

Population::evaluate(){

}


/*
 * Seleciona os x melhores
 */
QList<Element> Population::selection(QList<Population> populations){
    int size = populations.size();
    QList elements;
    for(int i=0; i<size; i++){
        for(int j=0; j<populations.at(i).size; j++){
            elements.append(populations.at(i).getElement(j));
        }
    }

}

Population *Population::mutation(float mutationTax){


}
