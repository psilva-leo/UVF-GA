#include "uvfobstacle.hh"

UVFObstacle::UVFObstacle(const Position &pos, const Velocity &vel) {
    _pos = pos;
    _vel = vel;

    _k0 = 1; // Fator multiplicativo da velocidade relativa
}

Position UVFObstacle::position() const {
    return _pos;
}

Velocity UVFObstacle::velocity() const {
    return _vel;
}

Position UVFObstacle::virtualPosition(const Position &posRobot, const Velocity &velRobot) const {
    double k0 = _k0;

    // Calculate s vector
    Velocity s(k0*(_vel.x()-velRobot.x()), k0*(_vel.y()-velRobot.y()));

    // Calculate virtual obstacle position
    float dist = sqrt(pow(posRobot.x()-_pos.x(), 2)+pow(posRobot.y()-_pos.y(), 2));
    float pox, poy;
    if(dist < s.abs()) {
        pox = _pos.x() + ((dist/s.abs())*s.x());
        poy = _pos.y() + ((dist/s.abs())*s.y());
    } else {
        pox = _pos.x() + s.x();
        poy = _pos.y() + s.y();
    }

    // Returns virtual obstacle position
    return Position(pox, poy);
}

