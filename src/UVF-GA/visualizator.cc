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

#include "visualizator.hh"
#include <QCoreApplication>
#include <UVF-GA/simulation/testcase/testcase.hh>
#include <iostream>

#define VIEW_STEP (1/60.0f) // seconds

Visualizator::Visualizator(GLSoccerView *view) {
    _view = view;
}

Visualizator::~Visualizator() {

}

void Visualizator::configMovement(const Position &origin, float originAngle, const Position &destination, float angleToLook, bool avoidRobots, bool avoidBall) {
    _origin = origin;
    _originAngle = originAngle;
    _destination = destination;
    _angleToLook = angleToLook;
    _avoidRobots = avoidRobots;
    _avoidBall = avoidBall;
}

void Visualizator::configLCtrParams(float kp, float ki, float kd, float limit) {
    _lKp = kp;
    _lKi = ki;
    _lKd = kd;
    _lLimit = limit;
}

void Visualizator::configACtrParams(float kp, float ki, float kd, float limit) {
    _aKp = kp;
    _aKi = ki;
    _aKd = kd;
    _aLimit = limit;
}

void Visualizator::configUVFParams(double de, double kr, double dmin, double delta) {
    _de = de;
    _kr = kr;
    _dmin = dmin;
    _delta = delta;
}

void Visualizator::configMaxSpeed(float maxASpeed, float maxLSpeed) {
    _maxASpeed = maxASpeed;
    _maxLSpeed = maxLSpeed;
}

void Visualizator::run() {
    // Create test case with better result
    TestCase test(10.0, VIEW_STEP);
    test.configUVFParams(_de, _kr, _dmin, _delta);
    test.configMaxSpeed(_maxASpeed, _maxLSpeed);

    test.configMovement(_origin, _originAngle, _destination, _angleToLook, _avoidRobots, _avoidBall);
    test.configACtrParams(_aKp, _aKi, _aKd, _aLimit);
    test.configLCtrParams(_lKp, _lKi, _lKd, _lLimit);

    // Get access to player and world
    Player *player = test.player();
    SSLWorld *world = test.world();

    test.initialize();
    while(player->hasReachedGoal()==false) {
        _view->updateDetection(world);

        test.iterate(VIEW_STEP);
        QThread::msleep(VIEW_STEP*1E3f);
    }
    test.finalize();
}
