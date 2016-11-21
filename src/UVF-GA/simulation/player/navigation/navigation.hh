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

#ifndef NAVIGATION_HH
#define NAVIGATION_HH

#include <UVF-GA/simulation/player/player.hh>
#include <UVF-GA/utils/utils.hh>
#include <UVF-GA/simulation/player/navigation/navigationalgorithm/navigationalgorithm.hh>
#include <UVF-GA/simulation/player/navigation/controlalgorithm/controlalgorithm.hh>
#include <QMutexLocker>

class Player;
class ControlAlgorithm;
class NavigationAlgorithm;

class Navigation {
public:
    Navigation(Player *player, SSLWorld *world);

    virtual ~Navigation();

    // Setters
    void setGoal(const Position &destination, const float &orientation, bool avoidRobots, bool avoidBall);
    void setMaxLSpeed(float maxLSpeed) { _maxLSpeed = fabs(maxLSpeed); }
    void setMaxASpeed(float maxASpeed) { _maxASpeed = fabs(maxASpeed); }

    // Getters
    float getDirection() const;
    float getDistance() const;
    float getMaxLSpeed() const { return _maxLSpeed; }
    float getMaxASpeed() const { return _maxASpeed; }

    // Interface functions
    void reset();
    double getLinearSpeed(float distError);
    double getAngularSpeed(float angularError);

    // Avoid
    void avoidRobots();
    void avoidBall();

    // PID
    void setLinearPIDParameters(double kp, double ki, double kd, double ilimit);
    void setAngularPIDParameters(double kp, double ki, double kd, double ilimit);
    void setUVFParameters(double de, double kr, double dmin, double delta, double k0);

private:
    // General access
    Player *_player;
    NavigationAlgorithm *_navAlg;
    mutable QMutex _navAlgMutex;
    SSLWorld *_world;

    // Internal
    ControlAlgorithm *_linCtrAlg;
    ControlAlgorithm *_angCtrAlg;

    // Direction and distance
    float _direction;
    float _distance;

    // Maximum speed
    float _maxLSpeed;
    float _maxASpeed;

    float _calculateLinearSpeed(float distError);
    float _calculateAngularSpeed(float angGoal );
};

#endif // NAVIGATION_HH
