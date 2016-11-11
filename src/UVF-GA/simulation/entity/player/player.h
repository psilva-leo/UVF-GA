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
    void goToLookTo(Position desiredPos, float angleToLook, bool avoidRobots);

    // Entity name (class name)
    QString name();

    // Getters
    Position position() const;
    float orientation() const;
    int playerId() const { return _id; }

private:
    // Player info
    int _id;

    // World
    SSLWorld *_world;    

    // Navigation
    Navigation *_nav;
};

#endif // PLAYER_H
