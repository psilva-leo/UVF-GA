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

#ifndef UVFOBSTACLE_H
#define UVFOBSTACLE_H

#include <UVF-GA/utils/utils.hh>

class UVFObstacle {
private:
    Position _pos;
    Velocity _vel;

    // Virtual obstacles calc
    double _k0; // Fator multiplicativo da velocidade relativa
public:
    UVFObstacle(const Position &pos, const Velocity &vel);

    Position position() const;
    Velocity velocity() const;
    Position virtualPosition(const Position &posRobot, const Velocity &velRobot) const;

    void setK0(float k0) { _k0 = k0; }
};

#endif // UVFOBSTACLE_H
