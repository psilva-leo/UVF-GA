#include "population.h"
#include <QMap>
#include <iomanip>

/**
 * @brief Creates a population with a number of individuals
 * @param size - Qty of elements inside the populaiton
 */
Population::Population(int size) : _better(size){
    this->_size = 0;

    for(int i=0; i<size; i++){
        Chromosome temp = Chromosome(GEN_SIZE);
        for(int j = 0; j<GEN_SIZE; j++){
            temp.getGen(j)->setValue(Utils::randf(MUT_MAX_LIMIT, MUT_MIN_LIMIT));
        }
        this->appendChromosome(temp);
    }

}

Population::~Population(){}

Chromosome* Population::getChromosome(int index){
    return &_pop[index];
}

void Population::appendChromosome(Chromosome newChromosome){
    this->_pop.append(newChromosome);
    this->_size++;
}

void Population::insertChromosome(Chromosome& newChromosome, int& position){
    this->_pop.insert(position, newChromosome);
}

//TODO: Population->Evaluate
void Population::evaluate(){
    for(int i=0; i<this->_size; i++){
        this->getChromosome(i)->evaluate();
    }
}

/**
 * @brief Select half of the population
 * @param QList of populations to choose from
 */
Population* Population::selection(QList<Population> populations){
    int size = populations.size();
    Population *selection = new Population(0);
    QMultiMap<double, Chromosome> map;   // Fitness, Chromosome

    for(int i=0; i<size; i++){
        for(int j=0; j<populations[i]._size; j++){
            // Multiplies for (-1) to be ordered in decrescent order.
            map.insert((-1)*populations[i].getChromosome(j)->getFitness(), *populations[i].getChromosome(j));
        }
    }

    QMapIterator<double, Chromosome> i(map);
    int count = 0;
    int selectNum = this->_size/2; // Number of Chromosomes to be selected
    while(i.hasNext() && count < selectNum){
        i.next();
        selection->appendChromosome(i.value());
        count++;
    }

    // TODO: Should this be here?
    // Selecting best chromosome
    if(this->_better.getFitness() < selection->getChromosome(0)->getFitness()){
        this->_better = *selection->getChromosome(0);
    }

    //TODO: Decide if prints or not the selected chromosomes
    cout << "##SELECTED CHORMOSOMES## coutn: " << count << " selecNum: " << selectNum << " size: " << selection->_size << endl;
    for(int i=0; i<selectNum; i++){
        Chromosome temp = *selection->getChromosome(i);
        cout << "Chromosome (" << i <<")\t-\t";
        cout << "FITNESS[" << fixed  << setprecision(5) << temp.getFitness() << "]\t";
        cout << "GEN";
        for(int j=0; j<GEN_SIZE; j++){
            cout << "[" << fixed  << setprecision(5) << temp.getGen(j)->getValue() << "]";
        }
        cout << endl;
    }
    cout << endl;

    return selection;
}

/**
 * @brief CrossOver with two parents getting half of the Genes from each of them.In casa of a odd number of genes,
 * the second parent gives one more Gene.
 * @return Population with crossover with size half of original.
 */
Population Population::crossOver(){
    Population crossOverPop = Population((this->_size)/2);
    int parent1GenesNum = this->getChromosome(0)->getGenQty()/2;

    for(int i=0; i<crossOverPop._size; i++){
        for(int j = 0; j<this->getChromosome(0)->getGenQty(); j++){
            if(j < parent1GenesNum){
                Genotype genAux = *this->getChromosome(2*i)->getGen(j);
                crossOverPop.getChromosome(i)->getGen(j)->setValue(genAux.getValue());
            }else{
                Genotype genAux = *this->getChromosome((2*i)+1)->getGen(j);
                crossOverPop.getChromosome(i)->getGen(j)->setValue(genAux.getValue());
            }
        }
    }

    cout << ">>> Fitness is 1.0 because of evaluate function" << endl;
    crossOverPop.evaluate();
    crossOverPop.print();
    return crossOverPop;
}

Population Population::mutation(float tax){
    int i;
    int qtyMuted = (int) floor((this->_pop[0].getGenQty())*tax);
    Population newPop = Population(this->_size);

    // Generate the index's list of the gene that will receive the mutation
    QList<int> mutedId;
    for(int i=0; i<qtyMuted; i++){
        int aux = rand()%(this->_pop[0].getGenQty());
        if (mutedId.contains(aux) || aux == this->_pop[0].getGenQty()){
            i--;
        }else{
            mutedId.append(aux);
        }

    }


    // Go over the population chromosome by chromosome
    for(i=0; i<this->_size; i++){
        // Mutate gene
        for(int j=0; j<_pop[0].getGenQty(); j++){
            if(mutedId.contains(j)){
                double value = this->_pop[i].getGen(j)->getValue()*Utils::randf(MUT_MAX_LIMIT, MUT_MIN_LIMIT);
                newPop.getChromosome(i)->getGen(j)->setValue(value);
            }else{
                double value = this->_pop[i].getGen(j)->getValue();
                newPop.getChromosome(i)->getGen(j)->setValue(value);
            }
        }
    }

    this->print();
    newPop.print();

    return newPop;
}

//Population *Population::mutation(float tax){
//    int i;
//    int qtyMuted = (int) floor(this->_size*tax);
//    Population *newPop = new Population(0);

//    // Gerate the index's list of the pupulation whose will receive the mutation
//    QList<int> mutedId;
//    for(int aux, i=0; i<qtyMuted; i++){
//        //Decrease the length of rand number to match with ID's
//        aux = rand()%(this->_size-i);
//        mutedId.append(aux);
//    }

//    Chromosome elemAux = Chromosome(_pop[0].getGenQty());
//    Genotype genAux;

//    // Seek the ID vector to make the mutaion
//    for(i=0; i<this->_size; i++){
//        // Copy the Element of List
//        elemAux = _pop.takeAt(mutedId.at(i));

//        // Removes from the list
//        _pop.removeAt(mutedId.at(i));

//        for(int j=0; j<elemAux.getGenQty(); j++){
//            // Gets the gen of the element to mutate
//            genAux = *elemAux.getGen(j);

////            // Uses the operator defined to multiply by the mutation factor
//            double value = genAux.getValue()*Utils::randf(MUT_MAX_LIMIT, MUT_MIN_LIMIT);

////            // Modify the gen inside the Element
//            genAux.setValue(value);
//        }

//        // Insert the Mutated Element inside the new population
//        newPop->_pop.append(elemAux);
//    }

//    // Insert last elements that doesn't receive mutation
//    int length = this->_pop.size();
//    for(i=0; i<length; i++){
//        elemAux = *this->getChromosome(i);
//        newPop->appendChromosome(elemAux);
//    }

//    return newPop;
//}

void Population::print(){
    int i, j;

    cout << "##POPULATION##" << endl;
    for(i=0; i<this->_size; i++){
        Chromosome auxChrom = *this->getChromosome(i);
        cout << "Chromosome (" << i <<")\t-\t";
        cout << "FITNESS[" << fixed  << setprecision(5) << auxChrom.getFitness() << "]\t";
        cout << "GEN";
        for(j=0; j<GEN_SIZE; j++){
            cout << "[" << fixed  << setprecision(5) << auxChrom.getGen(j)->getValue() << "]";
        }
        cout << "\n";
    }
    cout << endl;
}

/*
double Population::randf(double max, double min){
    int i;
    double acc;
    int signal = rand()%2;

    // Negative
    if(!signal){
        acc = (double) (rand()%((int)min));
        acc*=-1;
    }

    // Positive
    if(signal){
        acc = (double) (rand()%((int)max));
    }

    // Precision
    for(i=0; i<FRAND_PRECISION; i++){
        acc += (double)(rand()%(10))/(pow(10, i+1));;
    }

    if(!signal && acc<min){acc = min;}
    else if(signal && acc>max){acc = max;}

    return acc;
}
*/
