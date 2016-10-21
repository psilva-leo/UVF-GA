#ifndef UTILS_H
#define UTILS_H

#include<cstdio>
#include<cstdlib>
#include<cmath>

#define FRAND_PRECISION 5

class Utils
{
public:
    Utils();
    static double randf(int max, int min);
};

#endif // UTILS_H
