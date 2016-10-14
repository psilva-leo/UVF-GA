#ifndef POPULATION_H
#define POPULATION_H

#define FRAND_PRECISION 5
#define MUT_MAX_LIMIT 2.5
#define MUT_MIN_LIMIT -2.0

#include<element.h>
#include<cstdio>
#include<cstdlib>
#include<cmath>

class Population{

public:
    Population();

    Element getElement(int index);
    void evaluate();
    Population mutation(float tax);
    QList<Element> crossOver();
    Qlist<Element> selection(QList<Population> populations);

public:
    double randf(double max, double min);

private:
    int size;
    Element better;
    QList pop<Element>;

};

#endif // POPULATION_H
