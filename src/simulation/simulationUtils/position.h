#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    Position(float x, float y);
    Position();
    //~Position();

    void setPosition(float x, float y);
    float x() const;
    float y() const;

private:
    float _x;
    float _y;

};

#endif // POSITION_H
