#ifndef PLAYER_H
#define PLAYER_H

#include <simulation/entity/entity.hh>
#include <simulation/simulationUtils/simulationutils.h>
#include <3rdparty/sslworld/sslworld.h>

class Player : public Entity {
public:
    Player(int id, SSLWorld *world);
    void goToLookTo(Position desiredPos, Position posToLook, bool avoidRobots);

    // Entity name (class name)
    QString name();

    // Getters
    Position pos() { return _pos; }
    Position nextPos() { return _nextPos; }
    int playerId() { return _id; }

private:
    // Player info
    int _id;
    Position _pos;
    Position _nextPos;

    // World
    SSLWorld *_world;

    // Entity methods
    void initialization();
    void loop();
    void finalization();
};

#endif // PLAYER_H
