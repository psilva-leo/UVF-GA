#ifndef POPULATION_H
#define POPULATION_H

#define FRAND_PRECISION 5
#define MUT_MAX_LIMIT 2.5
#define MUT_MIN_LIMIT -2.0

#define GEN_SIZE 4

#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>


#include<element.h>
#include<genotype.h>
#include<utils.h>

using namespace std;

class Population{

public:
    Population(int size);
    ~Population();

    //Genetic Functions
    void generate();
    void evaluate();
    QList<Element> crossOver();
    Population *mutation(float tax);
    QList<Element> selection(QList<Population> populations);

    // Other Functins
    void insertElement(Element& newElement);
    Element getElement(int index);
    void print();

private:
    int _size;                   /* Population Length */
    Element _better;             /* Better Individual of Population */
    QList<Element> _pop;

};

#endif // POPULATION_H
