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

    // Commands
    void goToLookTo(Position desiredPos, float angleToLook, bool avoidRobots);
    void idle();



    // Entity name (class name)
    QString name();

    // Player info
    int playerId() const { return _id; }
    Position position() const;
    float orientation() const;

private:
    // Player info
    int _id;

    // World
    SSLWorld *_world;    

    // Navigation
    Navigation *_nav;

    // Private commands
    void setSpeed(float x, float y, float w);
};

#endif // PLAYER_H
