#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cmath>

// Utils include
#include "position.h"
#include "velocity.h"
#include "timer.hh"

#define FRAND_PRECISION 5
#define PI 3.141592654

class Utils {
public:
    static double randf(int max, int min);
};

#endif // UTILS_H
