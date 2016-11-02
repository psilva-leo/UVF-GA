#ifndef ELEMENT_H
#define ELEMENT_H

#include <QList>
#include <UVF-GA/geneticalgorithm/genotype.h>

class Chromosome{
public:
    Chromosome(int genQty);

    double getFitness();
    Genotype getGen(int i);
    void insertGen(Genotype& gen);
    double evaluate();
    int getGenQty();

private:
    int _genQty;
    QList<Genotype> _gen;
    double _fitness;
};

#endif // ELEMENT_H
