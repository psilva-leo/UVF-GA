#include "player.h"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

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
    _nav->setGoal(desiredPos, angleToLook, false, false);

    // Linear speeds calc
    float direction = _nav->getDirection();
    direction += direction - orientation() + PI;

    float distance  = _nav->getDistance();

    float speed = _nav->getLinearSpeed(distance);
    float xSpeed = speed*cos(direction);
    float ySpeed = speed*sin(direction);

    // Angular speed calc
    float aError = angleToLook - orientation();

    // Fix angular error
    if(aError >  PI) aError -= 2*PI;
    if(aError < -PI) aError += 2*PI;

    // Convert radians to degrees
    float wSpeed = _nav->getAngularSpeed(aError) * (180/PI);

//    std::cout << "X Speed: " << xSpeed << std::endl;
//    std::cout << "y Speed: " << ySpeed << std::endl;
//    std::cout << "W Speed: " << wSpeed << std::endl;
//    std::cout << "Distance: " << distance << std::endl;

    // Set speed
    _world->robots[_id]->setSpeed(xSpeed, ySpeed, wSpeed);
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

