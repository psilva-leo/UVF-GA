#ifndef ELEMENT_H
#define ELEMENT_H

#include <QList>
#include <genotype.h>

class Element{
public:
    Element(int size);
    Element();
    ~Element();

    Genotype getFitness();
    Genotype getGen(int i);
    void setGen(Genotype& gen, int position);
    double evaluate();
    int getSize();

private:
    int _size;
    QList<Genotype> _gen;
    double _fitness;
};

#endif // ELEMENT_H
