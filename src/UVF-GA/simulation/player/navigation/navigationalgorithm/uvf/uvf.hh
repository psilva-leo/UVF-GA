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

#ifndef UVF_HH
#define UVF_HH

#include <UVF-GA/simulation/player/navigation/navigationalgorithm/uvf/uvfobstacle.hh>
#include <UVF-GA/simulation/player/navigation/navigationalgorithm/navigationalgorithm.hh>
#include <cmath>
#include <QList>

class UVF : public NavigationAlgorithm {
public:
    UVF();
    ~UVF();

    void reset();

    // Config
    void setParameters(double de, double kr, double dmin, double delta);

    // Add obstacles
    void addBall(const Position &pos, const Velocity &vel);
    void addRobot(const Position &pos, const Velocity &vel);

    // Return results
    float getDirection() const;
private:
    // Run
    void run();

    // Obstacle avoidance
    void addObstacle(const Position &pos, const Velocity &vel);
    QList <UVFObstacle> _obstacles;

    // Auxiliar functions
    Position rotate(const Position &pos, float rot);
    Velocity rotate(const Velocity &vel, float rot);
    float getPhi(const Position &p, bool ccw, float de) const;
    float getPhiTUF(float x, float y, float de);
    float mergeVF(const Position &auf, float phiAUF, float phiTUF, Position tmpObst, Position tmpGoalPos);
    float gauss(float r) const;

    float wrapToPi(float angle);

    // Results
    float _resultantDirection;

    // UVF CONSTANTS
    double _de;
    double _kr;
    double _dmin;
    double _delta;
    double _k0;
};


#endif // UVF_HH
