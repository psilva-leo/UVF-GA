#include <population.h>

/**
 * @brief Creates a population with a number of individuals
 * @param size - Qty of elements inside the populaiton
 */
Population::Population(int size){
    this->_size = size;

    for(int i=0; i>size; i++){
        Element temp = Element(GEN_SIZE);
        _pop.append(temp);
    }
}

Population::~Population(){}

void Population::generate(){
    int j;

    Genotype genAux();

    for(QList<Element>::iterator i = _pop.begin(); i != _pop.end(); ++i)
    {
        for(j = 0; j<GEN_SIZE; j++)
        {
            genAux = Utils::randf(MUT_MAX_LIMIT, MUT_MIN_LIMIT);
            cout << genAux.getValue() << endl;
            i->setGen(genAux, j);
        }
    }
}

Element Population::getElement(int index){
    return _pop.at(index);
}

void Population::insertElement(Element& newElement){
    this->_pop.append(newElement);
}

//TODO: Population->Evaluate
void Population::evaluate(){

}


//TODO: Population->Selection
QList<Element> Population::selection(QList<Population> populations){
//    int size = populations.size();
//    QList<Element> elements;
//    for(int i=0; i<size; i++){
//        for(int j=0; j<populations.at(i).size; j++){
//            elements.append(populations.at(i).getElement(j));
//        }
//    }

}

Population *Population::mutation(float tax){
    int i;
    int qtyMuted = (int) floor(this->_size*tax);
    Population *newPop = new Population(0);

    // Gerate the index's list of the pupulation whose will receive the mutation
    QList<int> mutedId;
    for(int aux, i=0; i<qtyMuted; i++){
        //Decrease the length of rand number to match with ID's
        aux = rand()%(this->_size-i);
        mutedId.append(aux);
    }

    Element elemAux;
    Genotype genAux;

    // Seek the ID vector to make the mutaion
    for(i=0; i<this->_size; i++)
    {
        // Copy the Element of List
        elemAux = _pop.takeAt(mutedId.at(i));

        // Removes from the list
        _pop.removeAt(mutedId.at(i));

        for(int j=0; j<elemAux.getGenQty(); j++)
        {
            // Gets the gen of the element to mutate
            genAux = elemAux.getGen(j);

            // Uses the operator defined to multiply by the mutation factor
            genAux*Utils::randf(MUT_MAX_LIMIT, MUT_MIN_LIMIT);

            // Modify the gen inside the Element
            elemAux.setGen(genAux, j);
        }

        // Insert the Mutated Element inside the new population
        newPop->_pop.append(elemAux);
    }

    // Insert last elements that doesn't receive mutation
    int length = this->_pop.size();
    for(i=0; i<length; i++)
    {
        elemAux = this->getElement(i);
        newPop->insertElement(elemAux);
    }

    return newPop;
}

void Population::print(){
    int i, j;
    Element auxElem;

    for(i=0; i<this->_size; i++)
    {
        auxElem = this->getElement(i);
        std:cout << "(" << i <<")\t-\t";
        cout << "FITNESS[" << auxElem.getFitness().getValue() << "]\t";
        cout << "GEN";
        for(j=0; j<GEN_SIZE; j++)
        {
            cout << "[" << auxElem.getGen(j).getValue() << "]";
        }
        cout << "\n";
    }
}

/*
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
*/
