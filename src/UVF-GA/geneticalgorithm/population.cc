/***
 * SSC0713 - Sistemas Evolutivos Aplicados à Robótica
 * University of Sao Paulo (USP) at Sao Carlos
 *
 * Autores:
 * Guilherme Caixeta de Oliveira
 * Anderson Hiroshi de Siqueira
 * Leonardo Claudio de Paula e Silva
 * Lucas dos Santos Luchiari
 * Franco Saraiva
 *
 * This file is part of UVF-GA project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "population.hh"
#include <QMap>
#include <iomanip>

#include <UVF-GA/simulation/simulation.hh>

/**
 * @brief Creates a population with a number of individuals
 * @param size - Qty of elements inside the populaiton
 */
Population::Population(int size) : _better(GEN_SIZE) {
    this->_size = 0;

    for(int i=0; i<size; i++){
        Chromosome temp = Chromosome(GEN_SIZE);
        for(int j = 0; j<GEN_SIZE; j++){
            temp.getGen(j)->setValue(Utils::randf(MUT_MAX_LIMIT, MUT_MIN_LIMIT));
        }
        this->appendChromosome(temp);
    }

}

Chromosome* Population::getChromosome(int index) {
    return &_pop[index];
}

void Population::appendChromosome(Chromosome newChromosome) {
    this->_pop.append(newChromosome);
    this->_size++;
}

void Population::insertChromosome(Chromosome& newChromosome, int& position) {
    this->_pop.insert(position, newChromosome);
}

void Population::evaluate() {

    QList<UVFParams*> popParams0;
    QList<SpeedParams*> popParams1;

    // For each chromossome, generate params
    for(int i=0; i<_size; i++) {
        // UVF params
        UVFParams *params1 = new UVFParams();
        params1->de    = _pop[i].getGen(0)->getValue();
        params1->kr    = _pop[i].getGen(1)->getValue();
        params1->dmin  = _pop[i].getGen(2)->getValue();
        params1->delta = _pop[i].getGen(3)->getValue();
        params1->k0    = _pop[i].getGen(4)->getValue();
        popParams0.append(params1);

        // Speed params
        SpeedParams *params2 = new SpeedParams();
        params2->maxASpeed = _pop[i].getGen(5)->getValue();
        params2->maxLSpeed = _pop[i].getGen(6)->getValue();
        popParams1.append(params2);
    }

    // Simulate population
    Simulation simul;
    simul.setPopulationSize(_size);
    simul.setPopulationParams(popParams0);
    simul.setPopulationParams(popParams1);
    simul.run();

    // Get results
    QList<Results*> results = simul.results();

    // Update population fitness
    for(int i=0; i<_size; i++) {
        Results *result = results.at(i);

        // Calc fitness
        double fitness = 10*result->reachedGoal + 3/(0.3 + 2*result->angularError) +
                10/result->time + 3/(0.2 + result->linearError);
        _pop[i].setFitness(fitness);
    }

}

/**
 * @brief Select half of the population
 * @param QList of populations to choose from
 */
Population* Population::selection(QList<Population> populations) {
    int size = populations.size();
    int selectNum = this->_size; // Number of Chromosomes to be selected
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
    while(i.hasNext() && count < selectNum){
        i.next();
        selection->appendChromosome(i.value());
        count++;
    }

    // TODO: Should this be here?
    // Selecting best chromosome
    if(this->_better.getFitness() < selection->getChromosome(0)->getFitness()){
        selection->getBetter()->setFitness(selection->getChromosome(0)->getFitness());
        for(int i=0; i<_better.getGenQty(); i++){
            selection->getBetter()->getGen(i)->setValue(selection->getChromosome(0)->getGen(i)->getValue());
        }
    }else{
        selection->getBetter()->setFitness(_better.getFitness());
        for(int i=0; i<_better.getGenQty(); i++){
            selection->getBetter()->getGen(i)->setValue(_better.getGen(i)->getValue());
        }
    }

    //TODO: Decide if prints or not the selected chromosomes
//    cout << "##SELECTED CHROMOSOMES" << endl;
//    for(int i=0; i<selectNum; i++){
//        Chromosome temp = *selection->getChromosome(i);
//        cout << "Chromosome (" << i <<")\t-\t";
//        cout << "FITNESS[" << fixed  << setprecision(5) << temp.getFitness() << "]\t";
//        cout << "GEN";
//        for(int j=0; j<GEN_SIZE; j++){
//            cout << "[" << fixed  << setprecision(5) << temp.getGen(j)->getValue() << "]";
//        }
//        cout << endl;
//    }
//    cout << endl;

    return selection;
}

/**
 * @brief CrossOver with two parents getting half of the Genes from each of them.In casa of a odd number of genes,
 * the second parent gives one more Gene.
 * @return Population with crossover with size half of original.
 */
Population Population::crossOver(double rate) {
    Population crossOverPop = Population(_size);
    int parent1GenesNum = this->getChromosome(0)->getGenQty()/2;

    for(int i=0; i<crossOverPop._size; i+=2){
        if(rate > (((double) rand() / (RAND_MAX)))){
            Chromosome chromAux1 = *this->getChromosome(rand()%_size);
            Chromosome chromAux2 = *this->getChromosome(rand()%_size);
            // First child
            for(int j = 0; j<this->getChromosome(0)->getGenQty(); j++){

                if(j < parent1GenesNum){
                    crossOverPop.getChromosome(i)->getGen(j)->setValue(chromAux1.getGen(j)->getValue());
                }else{
                    crossOverPop.getChromosome(i)->getGen(j)->setValue(chromAux2.getGen(j)->getValue());
                }
            }

            // Second child
            if(i+1 < _size){
                for(int j = 0; j<this->getChromosome(0)->getGenQty(); j++){
                    if(j < parent1GenesNum){
                        crossOverPop.getChromosome(i+1)->getGen(j)->setValue(chromAux2.getGen(j)->getValue());
                    }else{
                        crossOverPop.getChromosome(i+1)->getGen(j)->setValue(chromAux1.getGen(j)->getValue());
                    }
                }
            }
        }else{
            // First child
            Chromosome chromAux1 = *this->getChromosome(rand()%_size);
            for(int j=0; j<this->getChromosome(0)->getGenQty(); j++){
                crossOverPop.getChromosome(i)->getGen(j)->setValue(chromAux1.getGen(j)->getValue());
            }

            // Second child
            if(i+1 < _size){
                Chromosome chromAux2 = *this->getChromosome(rand()%_size);
                for(int j=0; j<this->getChromosome(0)->getGenQty(); j++){
                    crossOverPop.getChromosome(i+1)->getGen(j)->setValue(chromAux2.getGen(j)->getValue());
                }
            }
        }
    }

    crossOverPop.evaluate();
//    cout << "###CROSSOVER\n";
//    crossOverPop.print();
    return crossOverPop;
}

Population Population::mutation(float tax) {
    int qtyMuted = (int) floor((this->_pop[0].getGenQty())*tax);
    Population newPop = Population(this->_size);
    double step = 0.15;

    // Go over the population chromosome by chromosome
    for(int i=0; i<this->_size; i++){
        // Generate the index's list of the gene that will receive the mutation
        QList<int> mutedId;
        for(int j=0; j<qtyMuted; j++){
            int aux = rand()%(this->_pop[0].getGenQty());
            if (mutedId.contains(aux) || aux == this->_pop[0].getGenQty()){
                j--;
            }else{
                mutedId.append(aux);
            }
        }


        // Mutate gene
        for(int j=0; j<_pop[0].getGenQty(); j++){
            if(mutedId.contains(j)){
                if(0.5 > (((double) rand() / (RAND_MAX)))){
                    step *= -1;
                }
                double value = this->_pop[i].getGen(j)->getValue()+step;
                newPop.getChromosome(i)->getGen(j)->setValue(value);
            }else{
                double value = this->_pop[i].getGen(j)->getValue();
                newPop.getChromosome(i)->getGen(j)->setValue(value);
            }
        }
    }

    newPop.evaluate();
//    cout << "###MUTATION\n";
//    newPop.print();

    return newPop;
}

void Population::print() {
    int i, j;

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
