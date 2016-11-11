#include "position.hh"

Position::Position(float x, float y) {
    _x = x;
    _y = y;
}

Position::Position() {
    _x = _y = 0.0;
}

void Position::setPosition(float x, float y) {
    _x = x;
    _y = y;
}

float Position::x() const {
    return _x;
}

float Position::y() const {
    return _y;
}
