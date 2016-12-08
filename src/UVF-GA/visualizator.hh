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

#ifndef VISUALIZATOR_HH
#define VISUALIZATOR_HH

#include <QThread>
#include <UVF-GA/utils/utils.hh>
#include <3rdparty/soccerview/soccerview.hh>

class Visualizator : public QThread {
public:
    Visualizator(GLSoccerView *view);
    ~Visualizator();

    void configMovement(const Position &origin, float originAngle, const Position &destination, float angleToLook, bool avoidRobots, bool avoidBall);
    void configLCtrParams(float kp, float ki, float kd, float limit);
    void configACtrParams(float kp, float ki, float kd, float limit);
    void configUVFParams(double de, double kr, double dmin, double delta);
    void configMaxSpeed(float maxASpeed, float maxLSpeed);

private:
    void run();

    GLSoccerView *_view;

    // Movement
    Position _origin;
    float _originAngle;
    Position _destination;
    float _angleToLook;
    bool _avoidRobots;
    bool _avoidBall;

    // Linear PID
    float _lKp, _lKi, _lKd, _lLimit;

    // Angular PID
    float _aKp, _aKi, _aKd, _aLimit;

    // UVF params
    float _de, _kr, _dmin, _delta;

    // Max speeds
    float _maxASpeed, _maxLSpeed;

};

#endif // VISALIZATOR_HH
