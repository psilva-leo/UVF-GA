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

#include "navigation.hh"

#include <UVF-GA/simulation/player/navigation/controlalgorithm/pid/pid.hh>
#include <UVF-GA/simulation/player/navigation/navigationalgorithm/uvf/uvf.hh>
#include <iostream>

Navigation::Navigation(Player *player, SSLWorld *world) {
    _player    = player;
    _navAlg    = new UVF();
    _linCtrAlg = new PID(1.5, 0.0, 0.0, 0.0);
    _angCtrAlg = new PID(2.0, 0.0, 0.0, 20.0);
    _world = world;
}

Navigation::~Navigation() {
    delete _navAlg;
    delete _linCtrAlg;
    delete _angCtrAlg;
}

void Navigation::setGoal(const Position &destination, const float &orientation, bool avoidRobots, bool avoidBall) {
    QMutexLocker locker(&_navAlgMutex);

    // Reset algorithm
    _navAlg->reset();

    // Set origin position and orientation
    _navAlg->setOrigin(_player->position(), _player->orientation());

    // Sets goal position and orientation
    _navAlg->setGoal(destination, orientation);

    // Calculate ball pos
    dReal ballX, ballY, ballZ;
    _world->ball->getBodyPosition(ballX, ballY, ballZ);

    // Add ball as repulsive
    if(avoidBall)
        _navAlg->addBall(Position(ballX, ballY), Velocity(0.0, 0.0));

    /// TODO: ADD ROBOTS
    // Adds robots as repulsive
    if(avoidRobots) {
//        QList<Player*> avOpPlayers = _opTeam->avPlayers().values();
//        for(int i=0; i<avOpPlayers.size(); i++) {
//            Player *opponent = avOpPlayers.at(i);

//            // Add robot as repulsive
//            _navAlg->addEnemyRobot(opponent->position(), opponent->velocity());
//        }
    }

}

float Navigation::getDirection() const {
    QMutexLocker locker(&_navAlgMutex);

    // Execute algorithm
    _navAlg->runNavigationAlgorithm();

    return _navAlg->getDirection();
}

float Navigation::getDistance() const {
    QMutexLocker locker(&_navAlgMutex);
    return _navAlg->getDistance();
}

void Navigation::reset() {
    _linCtrAlg->reset();
    _angCtrAlg->reset();
}

void Navigation::setLinearPIDParameters(double kp, double ki, double kd, double iLimit) {
    ControlAlgorithmParameters params;
    params.setPIDParameters(kp, ki, kd, iLimit);
    params.setTo(_linCtrAlg);
}

void Navigation::setAngularPIDParameters(double kp, double ki, double kd, double ilimit) {
    ControlAlgorithmParameters params;
    params.setPIDParameters(kp, ki, kd, ilimit);
    params.setTo(_angCtrAlg);
}

void Navigation::setUVFParameters(double de, double kr, double dmin, double delta, double k0) {
    _navAlg->setParameters(de, kr, dmin, delta, k0);
}

double Navigation::getLinearSpeed(float distError) {    
    // Iterate control algorithm
    float linearSpeed = _linCtrAlg->iterate(distError);

    // Limit to max linear speed
    if(linearSpeed < -_maxLSpeed) linearSpeed = -_maxLSpeed;
    if(linearSpeed >  _maxLSpeed) linearSpeed =  _maxLSpeed;

    return linearSpeed;
}

double Navigation::getAngularSpeed(float angularError) {
    float angularSpeed = 0.0;

    // Fix high angle
    if(angularError >  PI) angularError -= 2*PI;
    if(angularError < -PI) angularError += 2*PI;

    // Iterate control algorithm
    angularSpeed = _angCtrAlg->iterate(angularError);

    // Limit to max angular speed
    if(angularSpeed < -_maxASpeed) angularSpeed = -_maxASpeed;
    if(angularSpeed >  _maxASpeed) angularSpeed =  _maxASpeed;

    return angularSpeed;
}

void Navigation::avoidRobots() {
    for(int i=0; i < ROBOT_COUNT*2; i++) {
        if(_player->playerId() != i) {
            dReal x,y;
            _world->robots[i]->getXY(x,y);
            _navAlg->addRobot(Position(x, y), Velocity(0.0, 0.0));
        }
    }
}

void Navigation::avoidBall() {
    // Ball position
    dReal x, y, z;
    _world->ball->getBodyPosition(x,y,z,false);

    // Ball velocity
    /// TODO: onde achar velocidade?

    _navAlg->addBall(Position(x, y), Velocity(0.0, 0.0));
}
