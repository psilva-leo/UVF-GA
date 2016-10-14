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

Population *Population::mutation(float tax){
    int i;
    int qtyMuted = (int) flor(this->size*tax);
    Population *newPop = new Population();

    // Gerate the index's list of the pupulation whose will receive the mutation
    QList<int> mutedId;
    for(int aux, i=0; i<qtyMuted; i++){
        //Decrease the length of rand number to match with ID's
        aux = rand()%(this->size-i);
        mutedId.append(aux);
    }

    Element *aux;

    // Seek the ID vector to make the mutaion
    for(i=0; i<this->size; i++)
    {
        aux = this->pop.at(metedId.at(i));
        for(int j=0; j<aux->size; j++)
        {
            aux->gen.at(j) =* frand(MUT_MAX_LIMIT, MUT_MIN_LIMIT);
        }
        newPop->pop.append(aux);
    }

    // Insert last elements that doesn't receive mutation
    for(i=0; i<this->pop.size(); i++)
    {
        newPop->pop.append(this->pop.end());
    }

    return newPop;
}


double Population::randf(double max, double min)
{
    int i;
    double acc;
    int signal = rand()%2;

    // Negative
    if(!signal)
    {
        acc = (double) (rand()%((int)min));
        acc*=-1;
    }

    // Positive
    if(signal)
    {
        acc = (double) (rand()%((int)max));
    }

    // Precision
    for(i=0; i<FRAND_PRECISION; i++)
    {
        acc += (double)(rand()%(10))/(pow(10, i+1));;
    }
    if(!signal && acc<min){acc = min;}
    else if(signal && acc>max){acc = max;}

    return acc;
}
