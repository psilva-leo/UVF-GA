#ifndef VELOCITY_H
#define VELOCITY_H


class Velocity {
public:
    Velocity(float x, float y);

    float x()   const;
    float y()   const;
    float abs() const;

private:
    float _x;
    float _y;
    float _abs;
};

#endif // VELOCITY_H
