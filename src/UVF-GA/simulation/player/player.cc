/***
 * SSC0713 - Sistemas Evolutivos Aplicados à Robótica
 * University of Sao Paulo (USP) at Sao Carlos
 *
 * Autores:
 * Guilherme Caixeta de Oliveira
 * Anderson Hiroshi de Siqueira
 * Leonardo Claudio de Paula e Silva
 * Lucas dos Santos Luchiari
 * Franco Saraiva
 *
 * This file is part of UVF-GA project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "player.hh"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define LINEAR_ERROR 0.05f
#define ANGULAR_ERROR Utils::toRad(4)

Player::Player(int id, SSLWorld *world){
    _id = id;
    _idle = false;
    _world = world;   

    // Create navigation
    _nav = new Navigation(this, world);
    _nav->setLinearPIDParameters(1.5, 0.0, 0.0, 0.0);
    _nav->setAngularPIDParameters(1.5, 0.0, 0.0, 0.0);
    _nav->setMaxLSpeed(3.0);
    _nav->setMaxASpeed(4*PI);
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
    if(lError <= LINEAR_ERROR && fabs(aError) <= ANGULAR_ERROR)
        idle();
    else
        setSpeed(x, y, w);
}

void Player::idle() {
    _world->robots[_id]->setSpeed(0.0, 0.0, 0.0);
    _idle = true;
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

void Player::setUVFParameters(double de, double kr, double dmin, double delta) {
    _nav->setUVFParameters(de, kr, dmin, delta);
}

void Player::setMaxSpeed(float maxASpeed, float maxLSpeed) {
    _nav->setMaxASpeed(maxASpeed);
    _nav->setMaxLSpeed(maxLSpeed);
}

void Player::setSpeed(float x, float y, float w) {
    _world->robots[_id]->setSpeed(y, -x, w);
    _idle = false;
}

bool Player::hasReachedGoal() {
    return _idle;
}
