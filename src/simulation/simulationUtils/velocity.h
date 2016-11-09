#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity {
public:
    Velocity(float x, float y);
    Velocity();

    float x()   const;
    float y()   const;
    float abs() const;

    void setVelocity(float x, float y) { _x = x; _y = y; }

private:
    float _x;
    float _y;
    float _abs;
};

#endif // VELOCITY_H
