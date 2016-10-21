#ifndef GENOTYPE_H
#define GENOTYPE_H

#include<cstdio>
#include<cstdlib>

#define GEN_MAX_VALUE 10.0
#define GEN_MIN_VALUE -10.0

class Genotype
{
public:
    Genotype();
    Genotype(double min, double max);
    ~Genotype();

    void setMin(double min);
    void setMax(double max);
    void setValue(double x);
    double getValue();

    Genotype operator*(double nun);
    Genotype operator=(double nun);
private:
    double min, max, value;
};

#endif // GENOTYPE_H
