#include "position.h"

Position::Position(float x, float y) {
    _x = x;
    _y = y;
}

float Position::x() const {
    return _x;
}

float Position::y() const {
    return _y;
}
