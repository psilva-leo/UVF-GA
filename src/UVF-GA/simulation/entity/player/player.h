#ifndef PLAYER_H
#define PLAYER_H

#include <UVF-GA/utils/utils.h>
#include <3rdparty/sslworld/sslworld.h>
#include <UVF-GA/simulation/entity/player/navigation/navigation.hh>

class Navigation;

class Player {
public:
    Player(int id, SSLWorld *world);
    ~Player();
    void goToLookTo(Position desiredPos, float angleToLook, bool avoidRobots, bool avoidBall);

    // Entity name (class name)
    QString name();

    // Getters
    Position position() const;
    float orientation() const;
    int playerId() const { return _id; }

    // Setters
    void setLinearCtrlParameters(float kp, float ki, float kd, float limit);
    void setAngularCtrlParameters(float kp, float ki, float kd, float limit);
    void setUVFParameters(double de, double kr, double dmin, double delta, double k0);
    void setMaxSpeedAndAccel(float maxASpeed, float maxLSpeed, float maxLAccel);

private:
    // Player info
    int _id;

    // World
    SSLWorld *_world;    

    // Navigation
    Navigation *_nav;
};

#endif // PLAYER_H
