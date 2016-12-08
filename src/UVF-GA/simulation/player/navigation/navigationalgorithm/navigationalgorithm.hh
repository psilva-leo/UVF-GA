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

#ifndef NAVIGATIONALGORITHM_HH
#define NAVIGATIONALGORITHM_HH

#include <UVF-GA/utils/utils.hh>
#include <QMutexLocker>

class NavigationAlgorithm {
public:
    NavigationAlgorithm();
    virtual ~NavigationAlgorithm();

    // Access to Navigation
    void runNavigationAlgorithm();

    // Config
    virtual void setParameters(double de, double kr, double dmin, double delta) = 0;

    // Reset algorithm
    virtual void reset() = 0;

    // Set origin and goal
    void setOrigin(const Position &pos, const float &ori);
    void setGoal(const Position &pos, const float &ori);

    // Add obstacles
    virtual void addBall(const Position &pos, const Velocity &vel) = 0;
    virtual void addRobot(const Position &pos, const Velocity &vel) = 0;

    // Return results
    virtual float getDirection() const = 0;
    virtual float getDistance() const;

protected:
    // Origin access
    Position originPos() const { return _originPos; }
    float originOri() const { return _originOri; }

    // Goal access
    Position goalPos() const { return _goalPos; }
    float goalOri() const { return _goalOri; }

private:
    // Execute algorithm
    virtual void run() = 0;

    // NavigationAlgorithm Origin
    Position _originPos;
    float _originOri;

    // NavigationAlgorithm Goal
    Position _goalPos;
    float _goalOri;

    // Distance
    float _distance;
};

#endif // NAVIGATIONALGORITHM_HH
