#include "player.h"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define LINEAR_ERROR 0.04f

Player::Player(int id, SSLWorld *world){
    _id = id;
    _world = world;   

    // Create navigation
    _nav = new Navigation(this, world);
    _nav->setMaxASpeed(2.5*PI);
    _nav->setMaxLSpeed(3.0);
    _nav->setMaxLAcceleration(1.35);
}

Player::~Player() {
    // Delete Navigation
    delete _nav;
}

QString Player::name() {
    return "Player";
}

void Player::goToLookTo(Position desiredPos, float angleToLook, bool avoidRobots, bool avoidBall) {
    // Avoids
    if(avoidRobots) _nav->avoidRobots();
    if(avoidBall  ) _nav->avoidBall();

    // Set goal on navigation
    _nav->setGoal(desiredPos, angleToLook, avoidRobots, false);

    // Path-planning algorithm
    float direction = _nav->getDirection();
    direction = direction - orientation() + PI/2;

    // Linear speed
    float lError  = _nav->getDistance();
    float linearSpeed = _nav->getLinearSpeed(lError);
    float x = linearSpeed*cos(direction);
    float y = linearSpeed*sin(direction);

    // Angular speed
    float aError = angleToLook - orientation();
    float w = _nav->getAngularSpeed(aError);

    // Set command
//    if(Utils::distance(position(), desiredPos) <= LINEAR_ERROR)
//        idle();
//    else
        setSpeed(x, y, w);
}

void Player::idle() {
    _world->robots[_id]->setSpeed(0.0, 0.0, 0.0);
}

Position Player::position() const {
    dReal x, y;
    _world->robots[_id]->getXY(x, y);
    return Position(x, y);
}

float Player::orientation() const {
    return _world->robots[_id]->getDir()*(PI/180);
}

void Player::setLinearCtrlParameters(float kp, float ki, float kd, float limit) {
    _nav->setLinearPIDParameters(kp, ki, kd, limit);
}

void Player::setAngularCtrlParameters(float kp, float ki, float kd, float limit) {
    _nav->setAngularPIDParameters(kp, ki, kd, limit);
}

void Player::setUVFParameters(double de, double kr, double dmin, double delta, double k0) {
    _nav->setUVFParameters(de, kr, dmin, delta, k0);
}

void Player::setMaxSpeedAndAccel(float maxASpeed, float maxLSpeed, float maxLAccel) {
    _nav->setMaxASpeed(maxASpeed);
    _nav->setMaxLSpeed(maxLSpeed);
    _nav->setMaxLAcceleration(maxLAccel);
}

void Player::setSpeed(float x, float y, float w) {
    _world->robots[_id]->setSpeed(x, y, w);
}
