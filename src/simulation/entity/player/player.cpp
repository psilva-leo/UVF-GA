#include "player.h"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

Player::Player(int id, SSLWorld *world){
    _id = id;
    _world = world;   
    _nav   = new Navigation(this, world);
    configureNav();
}

Player::~Player() {
    delete _nav;
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
    float aError = angleToLook - _orientation;

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

void Player::configureNav() {
    _nav->setMaxASpeed(2.5*PI);
    _nav->setMaxLSpeed(3.0);
    _nav->setMaxLAcceleration(1.0);
    _nav->setMaxLAcceleration(1.35);

}

void Player::updatePlayer() {
    // Update position
    dReal x, y;
    _world->robots[_id]->getXY(x, y);
    _pos.setPosition((float)x, (float)y);

    // Update orientation (Degrees to Radians)
    _orientation = ( ((float) _world->robots[_id]->getDir()) * (PI/180) );
}
