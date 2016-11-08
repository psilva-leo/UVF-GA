#ifndef ELEMENT_H
#define ELEMENT_H

#include <QList>
#include <UVF-GA/geneticalgorithm/genotype.h>

class Chromosome{
public:
    Chromosome(int genQty);

    Genotype* getGen(int i);
    void insertGen(Genotype& gen);
    void evaluate();
    int getGenQty();
    double getFitness();
    void setFitness(double x);

private:
    int _genQty;
    double _fitness;
    QList<Genotype> _gen;
};

#endif // ELEMENT_H
