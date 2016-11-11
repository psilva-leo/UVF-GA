#ifndef PLAYER_H
#define PLAYER_H

#include <simulation/simulationUtils/simulationutils.h>
#include <3rdparty/sslworld/sslworld.h>
#include <simulation/entity/player/navigation/navigation.hh>

class Navigation;

class Player {
public:
    Player(int id, SSLWorld *world);
    ~Player();
    void goToLookTo(Position desiredPos, float angleToLook, bool avoidRobots);

    // Entity name (class name)
    QString name();

    // Updater
    void updatePlayer();

    // Getters
    Position position() { return _pos; }
    Position nextPos() { return _nextPos; }
    float orientation() { return _orientation; }
    int playerId() { return _id; }

private:
    // Player info
    int _id;
    Position _pos;
    Position _nextPos;
    float _orientation;

    // World
    SSLWorld *_world;    

    // Navigation
    Navigation *_nav;
    void configureNav();
};

#endif // PLAYER_H
