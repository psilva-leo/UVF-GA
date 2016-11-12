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

#include "uvfobstacle.hh"

UVFObstacle::UVFObstacle(const Position &pos, const Velocity &vel) {
    _pos = pos;
    _vel = vel;

    _k0 = 1; // Fator multiplicativo da velocidade relativa
}

Position UVFObstacle::position() const {
    return _pos;
}

Velocity UVFObstacle::velocity() const {
    return _vel;
}

Position UVFObstacle::virtualPosition(const Position &posRobot, const Velocity &velRobot) const {
    double k0 = _k0;

    // Calculate s vector
    Velocity s(k0*(_vel.x()-velRobot.x()), k0*(_vel.y()-velRobot.y()));

    // Calculate virtual obstacle position
    float dist = sqrt(pow(posRobot.x()-_pos.x(), 2)+pow(posRobot.y()-_pos.y(), 2));
    float pox, poy;
    if(dist < s.abs()) {
        pox = _pos.x() + ((dist/s.abs())*s.x());
        poy = _pos.y() + ((dist/s.abs())*s.y());
    } else {
        pox = _pos.x() + s.x();
        poy = _pos.y() + s.y();
    }

    // Returns virtual obstacle position
    return Position(pox, poy);
}

