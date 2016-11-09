#include "player.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

Player::Player(int id, SSLWorld *world) : Entity(Entity::ENT_PLAYER) {
    _id = id;
    _world = world;   
    _nav   = new Navigation(this, world);
}

QString Player::name() {
    return "PLAYER";
}

void Player::goToLookTo(Position desiredPos, float angleToLook, bool avoidRobots) {
    // Set goal
    _nav->setGoal(desiredPos, angleToLook, false, false);

    // Linear speeds calc
    float direction = _nav->getDirection();
    float distance  = _nav->getDistance();

    float speed = _nav->getLinearSpeed(distance);

    float xSpeed = speed*cos(direction);
    float ySpeed = speed*sin(direction);

    // Angular speed calc
    float aError = direction - _orientation;

    // Limit error
    if(aError >  PI) aError =  PI;
    if(aError < -PI) aError = -PI;

    float wSpeed = _nav->getAngularSpeed(aError);

    // Set speed
    _world->robots[_id]->setSpeed(xSpeed, ySpeed, wSpeed);
}

void Player::initialization() {
    printf("[PLAYER %2d] thread started.\n", playerId());
}

void Player::loop() {
    // Update position
    dReal x, y;
    _world->robots[_id]->getXY(x, y);
    _pos.setPosition((float)x, (float)y);

    // Update orientation
    _orientation = (float) _world->robots[_id]->getDir();
}

void Player::finalization() {
    printf("[PLAYER %2d] thread ended.\n", playerId());
}

void Player::configureNav() {
    _nav->setMaxASpeed(2.0);
    _nav->setMaxLSpeed(2.0);
    _nav->setMaxLAcceleration(1.0);
}
