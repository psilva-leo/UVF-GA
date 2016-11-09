#include "velocity.h"
#include <cmath>

Velocity::Velocity(float x, float y) {
    _x   = x;
    _y   = y;
    _abs = sqrt(pow(x,2)+pow(y,2));
}

float Velocity::x()   const {
    return _x;
}

float Velocity::y()   const {
    return _y;
}

float Velocity::abs() const {
    return _abs;
}
