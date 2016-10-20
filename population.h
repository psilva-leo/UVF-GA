#ifndef POPULATION_H
#define POPULATION_H

#define FRAND_PRECISION 5
#define MUT_MAX_LIMIT 2.5
#define MUT_MIN_LIMIT -2.0

#define GEN_SIZE 4

#include<cstdio>
#include<cstdlib>
#include<cmath>

#include<element.h>
#include<genotype.h>
#include<utils.h>

class Population{

public:
    Population(int size);
    ~Population();

    void evaluate();
    void insertElement(Element& newElement);
    Element getElement(int index);
    Population *mutation(float tax);
    QList<Element> crossOver();
    QList<Element> selection(QList<Population> populations);

//public:
//    double randf(double max, double min);

private:
    int size;
    Element better;
    QList<Element> _pop;

};

#endif // POPULATION_H
