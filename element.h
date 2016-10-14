#ifndef ELEMENT_H
#define ELEMENT_H

#include <QList>

class Element
{
public:
    Element();
    ~Element();

    double getFitness();
    double evaluate();
private:
    int size;
    QList<Genotype> gen;
    double fitness;
};

#endif // ELEMENT_H
