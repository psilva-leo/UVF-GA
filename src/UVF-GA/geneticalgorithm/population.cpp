#include "population.h"
#include <QMap>
#include <iomanip>

/**
 * @brief Creates a population with a number of individuals
 * @param size - Qty of elements inside the populaiton
 */
Population::Population(int size) : _better(size){
    this->_size = size;

    for(int i=0; i>size; i++){
        Chromosome temp = Chromosome(GEN_SIZE);
        _pop.append(temp);
    }
}

Population::~Population(){}

void Population::generate(){
    int j;
    Genotype genAux = Genotype();

    for(int i=0; i<this->_size; i++){
        Chromosome temp = Chromosome(GEN_SIZE);
        for(j = 0; j<GEN_SIZE; j++){
            genAux.setValue(Utils::randf(MUT_MAX_LIMIT, MUT_MIN_LIMIT));
            temp.insertGen(genAux);
        }
        this->insertChromosome(temp);
    }
}

Chromosome Population::getChromosome(int index){
    return _pop[index];
}

void Population::insertChromosome(Chromosome& newElement){
    this->_pop.append(newElement);
}

//TODO: Population->Evaluate
void Population::evaluate(){

}


//TODO: Population->Selection
/*
 * Select half of the population
 */
QList<Chromosome> Population::selection(QList<Population> populations){
    int size = populations.size();
    QList<Chromosome> selection;
    QMap<double, Chromosome> map;   // Fitness, Chromosome
    for(int i=0; i<size; i++){
        for(int j=0; j<populations[i]._size; j++){
            // Multiplies for (-1) to be ordered in decrescent order.
            map.insert((-1)*populations[i].getChromosome(j).getFitness(), populations[i].getChromosome(j));
        }
    }


    QMapIterator<double, Chromosome> i(map);
    int count = 0;
    int selectNum = populations[0]._size/2; // Number of Chromosomes to be selected
    while(i.hasNext() && count < selectNum){
        i.next();
        selection.append(i.value());
        count++;
    }

    //TODO: Decide if prints or not the selected chromosomes
    cout << "\n##SELECTED CHORMOSOMES##" << endl;
    for(int i=0; i<selection.size(); i++){
        Chromosome temp = selection[i];
        cout << "Chromosome (" << i <<")\t-\t";
        cout << "FITNESS[" << fixed  << setprecision(5) << temp.getFitness() << "]\t";
        cout << "GEN";
        for(int j=0; j<GEN_SIZE; j++){
            cout << "[" << fixed  << setprecision(5) << temp.getGen(j).getValue() << "]";
        }
        cout << "\n";

    }

    return selection;
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

    Chromosome elemAux = Chromosome(_pop[0].getGenQty());
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
            double value = genAux.getValue()*Utils::randf(MUT_MAX_LIMIT, MUT_MIN_LIMIT);

            // Modify the gen inside the Element
            genAux.setValue(value);
        }

        // Insert the Mutated Element inside the new population
        newPop->_pop.append(elemAux);
    }

    // Insert last elements that doesn't receive mutation
    int length = this->_pop.size();
    for(i=0; i<length; i++)
    {
        elemAux = this->getChromosome(i);
        newPop->insertChromosome(elemAux);
    }

    return newPop;
}

void Population::print(){
    int i, j;

    cout << "\n##POPULATION##" << endl;
    for(i=0; i<this->_size; i++){
        Chromosome auxChrom = this->getChromosome(i);
        cout << "Chromosome (" << i <<")\t-\t";
        cout << "FITNESS[" << fixed  << setprecision(5) << auxChrom.getFitness() << "]\t";
        cout << "GEN";
        for(j=0; j<GEN_SIZE; j++){
            cout << "[" << fixed  << setprecision(5) << auxChrom.getGen(j).getValue() << "]";
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
