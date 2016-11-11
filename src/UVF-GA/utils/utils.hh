#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cmath>

// Utils include
#include "position/position.hh"
#include "velocity/velocity.hh"
#include "timer/timer.hh"

#define FRAND_PRECISION 5
#define PI 3.141592654

class Utils {
public:
    static double randf(int max, int min);
    static float distance(const Position &p1, const Position &p2);
};

#endif // UTILS_H
