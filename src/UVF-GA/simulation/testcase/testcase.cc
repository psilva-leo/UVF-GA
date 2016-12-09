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

#include "testcase.hh"
#include <iostream>

#define A_ERROR Utils::toRad(4)
#define OBSTACLE_COLLISION_RADIUS 0.25f

TestCase::TestCase(float runTimeoutSec, float simulationStepSec) : _simulationTimeoutSec(runTimeoutSec), _simulationStepSec(simulationStepSec) {
    _world = new SSLWorld();
    _player = new Player(0, _world);
    _reachedGoal = false;
    _linError = 100.0;
    _angError = 100.0;
    _angTime  = 100.0;
    _hasReachedTargetAngle = false;
    _entryAngError = 100.0;
    _collisions = 0;

    // Default movement
    configMovement(Position(0.0, 0.0), 0.0, Position(1.0, 1.0), PI/4, false, false);

    // Set loop time (higher speed possible)
    this->setLoopTime(0);
}

TestCase::~TestCase() {
    delete _world;
    delete _player;
}

QString TestCase::name() {
    return "TestCase";
}

void TestCase::initialization() {
    initialize();
}

void TestCase::loop() {
    iterate(_simulationStepSec);
}

void TestCase::finalization() {
    finalize();
}

void TestCase::initialize() {
    // Set robot origin position and angle
    _world->robots[0]->setXY(_origin.x(), _origin.y());
    _world->robots[0]->setDir(Utils::toDeg(_originAngle));

    // Randomize robots positions
    for(int i=1; i<2*ROBOT_COUNT; i++) {

        // Get original pos
        dReal x, y;
        _world->robots[i]->getXY(x, y);

        // Randomize
        float dx = ((float)rand()/RAND_MAX)*0.6 - 0.3;
        float dy = ((float)rand()/RAND_MAX)*0.6 - 0.3;
        _world->robots[i]->setXY(x+dx, y+dy);
    }

    // Remove ball from field
    _world->ball->setBodyPosition(0.0, -10, 0.0);

    // Initialize timers
    _linTime = 0.0f;
}

void TestCase::iterate(float step) {
    // Go to look to
    _player->goToLookTo(_destination, _targetAngle, _avoidRobots, _avoidBall);

    // Step world
    _world->step(step);

    // Update entry ang error
    Position delta(_player->position().x()-_lastPos.x(), _player->position().y()-_lastPos.y());
    double entryAng = atan2(delta.y(), delta.x());
    _entryAngError = fabs(_targetAngle - entryAng);
    _lastPos = _player->position();

    // Check collisions
    for(int i=0; i<2*ROBOT_COUNT; i++) {
        // Discard self player
        if(i==_player->playerId())
            continue;

        // Get obstacle position
        dReal x, y;
        _world->robots[i]->getXY(x, y);
        Position obstacle(x, y);

        // Update collision counter
        if(Utils::distance(_player->position(), obstacle) <= OBSTACLE_COLLISION_RADIUS) {
            if(_collisionRobots.contains(i)==false) {
                _collisions++;
                _collisionRobots.append(i);
            }
        }
    }


    // Update time
    _linTime += step;

    // Update angular error
    _angError = fabs(_player->orientation() - _targetAngle);

    // If has reached target angle
    if(_hasReachedTargetAngle==false && _angError <= A_ERROR) {
        _hasReachedTargetAngle = true;
        _angTime = _linTime;

    } else if(_hasReachedTargetAngle && _angError >= 1.25*A_ERROR) {
        _hasReachedTargetAngle = false;

    }

    // STOP CONDITION: time out
    if(_linTime >= _simulationTimeoutSec) {
        _reachedGoal = false;
        _linError = Utils::distance(_player->position(), _destination);

        // Stop entity
        this->stopEntity();
    }

    // STOP CONDITION: player reached goal
    if(_player->hasReachedGoal()) {
        _reachedGoal = true;
        _linError = Utils::distance(_player->position(), _destination);

        // Stop entity
        this->stopEntity();
    }
}

void TestCase::finalize() {

}

void TestCase::configLCtrParams(float kp, float ki, float kd, float limit) {
    _player->setLinearCtrlParameters(kp, ki, kd, limit);
}

void TestCase::configACtrParams(float kp, float ki, float kd, float limit) {
    _player->setAngularCtrlParameters(kp, ki, kd, limit);
}

void TestCase::configUVFParams(double de, double kr, double dmin, double delta) {
    _player->setUVFParameters(de, kr, dmin, delta);
}

void TestCase::configMaxSpeed(float maxASpeed, float maxLSpeed) {
    _player->setMaxSpeed(maxASpeed, maxLSpeed);
}

void TestCase::configMovement(const Position &origin, float originAngle, const Position &destination, float angleToLook, bool avoidRobots, bool avoidBall) {
    _origin = origin;
    _originAngle = originAngle;
    _destination = destination;
    _targetAngle = angleToLook;
    _avoidBall = avoidBall;
    _avoidRobots = avoidRobots;
}
