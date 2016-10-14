#include "genotype.h"

Genotype::Genotype(double min, double max)
{
    this->min = min;
    this->max = max;

    this->value = (double)rand()/RAND_MAX;
}

Genotype::setMax(double max){
    this->max = max;
}

Genotype::setMin(double min){
    this->min = min;
}
