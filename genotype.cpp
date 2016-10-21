#include <genotype.h>

Genotype::Genotype(){}

Genotype::~Genotype(){
    this->min = 0.0;
    this->max = 0.0;

    this->value = 0.0;
}

Genotype::Genotype(double min, double max)
{
    this->min = min;
    this->max = max;

    this->value = (double)rand()/RAND_MAX;
}

double Genotype::getValue(){
    return this->value;
}

void Genotype::setMax(double max){
    this->max = max;
}

void Genotype::setMin(double min){
    this->min = min;
}

void Genotype::setValue(double x){
    this->value = x;
}

Genotype Genotype::operator*(double nun){
    Genotype aux(0,0);
    aux.setValue(this->value*nun);
    return aux;
}

Genotype Genotype::operator=(double num){
    Genotype aux;
    aux.setValue(num);
    return aux;
}
