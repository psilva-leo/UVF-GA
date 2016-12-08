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

#ifndef PLAYER_H
#define PLAYER_H

#include <UVF-GA/utils/utils.hh>
#include <3rdparty/sslworld/sslworld.hh>
#include <UVF-GA/simulation/player/navigation/navigation.hh>

class Navigation;

class Player {
public:
    Player(int id, SSLWorld *world);
    ~Player();

    // Commands
    void goToLookTo(Position desiredPos, float angleToLook, bool avoidRobots, bool avoidBall);
    void idle();

    // Entity name (class name)
    QString name();

    // Player info
    int playerId() const { return _id; }
    Position position() const;
    float orientation() const;
    bool hasReachedGoal();

    // Setters
    void setLinearCtrlParameters(float kp, float ki, float kd, float limit);
    void setAngularCtrlParameters(float kp, float ki, float kd, float limit);
    void setUVFParameters(double de, double kr, double dmin, double delta);
    void setMaxSpeed(float maxASpeed, float maxLSpeed);

private:
    // Player info
    int _id;
    bool _idle;

    // World
    SSLWorld *_world;    

    // Navigation
    Navigation *_nav;

    // Private commands
    void setSpeed(float x, float y, float w);
};

#endif // PLAYER_H
