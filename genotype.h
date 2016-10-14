#ifndef GENOTYPE_H
#define GENOTYPE_H

#include<cstdio>
#include<cstdlib>

class Genotype
{
public:
    Genotype(double min, double max);
    ~Genotype();

    void setMin(double min);
    void setMax(double max);
    void setValue(double x);
    double getValue();
private:
    double min, max, value;
};

#endif // GENOTYPE_H
