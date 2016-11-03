#ifndef POPULATION_H
#define POPULATION_H

#define FRAND_PRECISION 5
#define MUT_MAX_LIMIT 2.5
#define MUT_MIN_LIMIT -2.0

#define GEN_SIZE 4

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "chromosome.h"
#include "genotype.h"
#include <UVF-GA/utils/utils.h>

using namespace std;

class Population{

public:
    Population(int size);
    ~Population();

    //Genetic Functions
    void generate();
    void evaluate();
    Population crossOver();
    Population *mutation(float tax);
    QList<Chromosome> selection(QList<Population> populations);

    // Other Functins
    void appendChromosome(Chromosome newElement);
    void insertChromosome(Chromosome& newChromosome, int& position);
    Chromosome* getChromosome(int index);
    void print();

private:
    int _size;                   /* Population Length */
    Chromosome _better;             /* Better Individual of Population */
    QList<Chromosome> _pop;

};

#endif // POPULATION_H
