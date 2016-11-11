#ifndef UVFOBSTACLE_H
#define UVFOBSTACLE_H

#include <UVF-GA/utils/utils.hh>

class UVFObstacle {
private:
    Position _pos;
    Velocity _vel;

    // Virtual obstacles calc
    double _k0; // Fator multiplicativo da velocidade relativa
public:
    UVFObstacle(const Position &pos, const Velocity &vel);

    Position position() const;
    Velocity velocity() const;
    Position virtualPosition(const Position &posRobot, const Velocity &velRobot) const;

    void setK0(float k0) { _k0 = k0; }
};

#endif // UVFOBSTACLE_H
