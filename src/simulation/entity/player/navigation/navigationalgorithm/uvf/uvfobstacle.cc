/***
 * Warthog Robotics
 * University of Sao Paulo (USP) at Sao Carlos
 * http://www.warthog.sc.usp.br/
 *
 * This file is part of WRCoach project.
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
 ***/

#include "uvfobstacle.hh"
#include <WRCoach/const/uvfconstants.hh>
#include <WRCoach/utils/utils.hh>

UVFObstacle::UVFObstacle(const Position &pos, const Velocity &vel) {
    _pos = pos;
    _vel = vel;
}

Position UVFObstacle::position() const {
    return _pos;
}

Velocity UVFObstacle::velocity() const {
    return _vel;
}

Position UVFObstacle::virtualPosition(const Position &posRobot, const Velocity &velRobot) const {
    double k0 = UVFConstants::k0();

    // Calculate s vector
    Velocity s(true, k0*(_vel.x()-velRobot.x()), k0*(_vel.y()-velRobot.y()));

    // Calculate virtual obstacle position
    float dist = WR::Utils::distance(posRobot, _pos);
    float pox, poy;
    if(dist < s.abs()) {
        pox = _pos.x() + ((dist/s.abs())*s.x());
        poy = _pos.y() + ((dist/s.abs())*s.y());
    } else {
        pox = _pos.x() + s.x();
        poy = _pos.y() + s.y();
    }

    // Returns virtual obstacle position
    return Position(true, pox, poy, 0.0);
}

