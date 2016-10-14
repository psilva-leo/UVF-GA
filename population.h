#ifndef POPULATION_H
#define POPULATION_H

#include<element.h>

class Population{

public:
    Population();

    Element getElement(int index);

    void evaluate();
    Qlist<Element> selection(QList<Population> populations);
    void mutation();
    QList<Element> crossOver();

private:
    int size;
    Element better;
    QList pop<Element>;

};

#endif // POPULATION_H
