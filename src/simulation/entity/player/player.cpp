#include "player.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

Player::Player(int id, SSLWorld *world) : Entity(Entity::ENT_PLAYER) {
    _id = id;
    _world = world;
}

QString Player::name() {
    return "PLAYER";
}

void Player::goToLookTo(Position desiredPos, Position posToLook, bool avoidRobots) {
    _world->robots[_id]->setSpeed(0.0, 1.0, 0.0);
}

void Player::initialization() {
    printf("[PLAYER %2d] thread started.\n", playerId());
}

void Player::loop() {

}

void Player::finalization() {
    printf("[PLAYER %2d] thread ended.\n", playerId());
}
