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

#include "uvf.hh"
#include <WRCoach/entity/locations.hh>
#include <WRCoach/const/uvfconstants.hh>

UVF::UVF() {
    reset();
}

UVF::~UVF() {

}

void UVF::reset() {
    _resultantDirection.setUnknown();
    _obstacles.clear();
}


void UVF::addBall(const Position &pos, const Velocity &vel) {
    addObstacle(pos, vel);
}

void UVF::addGoalArea(const Position &pos) {
    // TODO
}

void UVF::addOwnRobot(const Position &pos, const Velocity &vel) {
    addObstacle(pos, vel);
}

void UVF::addEnemyRobot(const Position &pos, const Velocity &vel) {
    addObstacle(pos, vel);
}

Angle UVF::getDirection() const {
    return _resultantDirection;
}

UVF* UVF::clone() const {
    return new UVF(*this);
}

Position UVF::rotate(const Position &pos, float rot){
    return Position(true, pos.x()*cos(rot) - pos.y()*sin(rot), pos.x()*sin(rot) + pos.y()*cos(rot), pos.z());
}

Velocity UVF::rotate(const Velocity &vel, float rot) {
    return Velocity(true, vel.x()*cos(rot) - vel.y()*sin(rot), vel.x()*sin(rot) + vel.y()*cos(rot));
}

float UVF::getPhiTUF(float x, float y, float de){
    float yL = y + de;
    float yR = y - de;
    Position pL(true, x, yL, 0.0);
    Position pR(true, x, yR, 0.0);

    if(y < -de) {
        return getPhi(pL, true, de);

    } else if(y >= de) {
        return getPhi(pR, false, de);

    } else {
        float phiHCCW = getPhi(pR, false, de);
        float phiHCW = getPhi(pL, true, de);

        Position NhCW(true, cos(phiHCW), sin(phiHCW), 0.0);
        Position NhCCW(true, cos(phiHCCW), sin(phiHCCW), 0.0);

        float phiX = ((fabs(yL)*NhCCW.x()) + (fabs(yR)*NhCW.x()))/(2*de);
        float phiY = ((fabs(yL)*NhCCW.y()) + (fabs(yR)*NhCW.y()))/(2*de);

        return atan2(phiY, phiX);
    }
}

float UVF::mergeVF(const Position &auf, float phiAUF, float phiTUF, Position tmpObst, Position tmpGoalPos){
    float phi;

    float dmin = UVFConstants::dmin();
    float r = sqrt(pow(auf.x(), 2) + pow(auf.y(), 2));
    if(r <= dmin) {
        phi = phiAUF;

    } else {
        // Merge
        float g = gauss(r-dmin);
        float diff = fabs(phiAUF - phiTUF);
        if(diff > GEARSystem::Angle::pi)
            diff = fabs(GEARSystem::Angle::twoPi - diff);

        // Calc phi
        float cross = cos(phiAUF)*sin(phiTUF) - sin(phiAUF)*cos(phiTUF);
        int s;
        if(cross > 0){
            s = -1;
        } else {
            s = 1;
        }
        phi = phiTUF + s*diff*g;

        // Fix phi
        Position vecObst(true, tmpObst.x() - tmpGoalPos.x(), tmpObst.y() - tmpGoalPos.y(), 0.0);
        if(auf.x() < 0) {
            if(!(vecObst.y() > 0 && vecObst.x() > 0 && auf.y() < 0 && auf.x() < 0)) {
                if(!(vecObst.y() < 0 && vecObst.x() > 0 && auf.y()>0 && auf.x()<0)) {
                    if(!(vecObst.y() > 0 && auf.y() >= 0 && auf.x() < 0)) {
                        if(!(vecObst.y() < 0 && auf.y() <= 0 && auf.x() < 0)) {
                            phi = phiTUF + (phiAUF-phiTUF)*g;
                        }
                    }
                }
            }
        }
    }

    return phi;
}

void UVF::run() {
    if(originPos().isUnknown() || goalPos().isUnknown() || goalOri().isUnknown()) {
        std::cout << "[WARNING] UVF: originPos, goalPos or goalOri is unknown!\n";
        return;
    }

    float targetOri = goalOri().value() + GEARSystem::Angle::pi;;

    // Get rotation
    float rot = wrapToPi(targetOri);
    rot = GEARSystem::Angle::pi - rot;

    Position tmpOriginPos = rotate(originPos(), rot);
    Position tmpGoalPos = rotate(goalPos(), rot);

    // Translate x-y axis
    float x = tmpOriginPos.x() - tmpGoalPos.x();
    float y = tmpOriginPos.y() - tmpGoalPos.y();

    // Iterate through obstacles
    float phi = 0.0;

    float constant = 1.8;
    float de = 0.7;//= UVFConstants::de()/**originVel().abs()*constant*/;

    WR::Utils::limitValue(&de, 0.07, 0.10);

//    std::cout << "\nde = " << de;

    // Calculate phiTUF
    float phiTUF = getPhiTUF(x, y, de);

    for(int i=0; i<_obstacles.size(); i++) { // Traverse through QList
        UVFObstacle obst = _obstacles.at(i);

        // Fetch obstacle and rotate
        Velocity tmpObstVel = rotate(obst.velocity(), rot);
//        Position tmpObstPos = rotate(obst.position(), rot);
        Position tmpObstPos = rotate(obst.virtualPosition(tmpObstPos, tmpObstVel), rot);

        // Obstacle close to goal position exception
        if(WR::Utils::distance(tmpObstPos, tmpGoalPos) < 0.10)
            continue;

        // Calculate phiAUF
        Position auf(true, tmpOriginPos.x() - tmpObstPos.x(), tmpOriginPos.y() - tmpObstPos.y(), 0.0);
        float phiAUF = atan2(auf.y(), auf.x());

        // Wrap
        phiTUF = wrapToPi(phiTUF);
        phiAUF = wrapToPi(phiAUF);

        // Calculate phi
        phi = mergeVF(auf, phiAUF, phiTUF, tmpObstPos, tmpGoalPos);

        // Update phiTUF
        phiTUF = phi;
    }
    phi = phiTUF;

    // Store result
    _resultantDirection.setValue(phi-rot);
}

void UVF::addObstacle(const Position &pos, const Velocity &vel) {
    _obstacles.append(UVFObstacle(pos, vel));
}

float UVF::getPhi(const Position &p, bool ccw, float de) const {
    float kr = UVFConstants::kr();

    float signal = (ccw? -1.0 : 1.0);
    float theta = atan2(p.y(), p.x());
    float ro = sqrt(pow(p.x(), 2) + pow(p.y(), 2));
    if(ro > de)
        return theta + signal*(GEARSystem::Angle::pi/2.0)*(2.0-(de+kr)/(ro+kr));
    else
        return theta + signal*(GEARSystem::Angle::pi/2.0)*sqrt(ro/de);
}

float UVF::gauss(float r) const {
    float delta = UVFConstants::delta();
    return exp(-(pow(r,2))/(2*pow(delta,2)));
}

float UVF::wrapToPi(float angle) {
    while(angle < -GEARSystem::Angle::pi)
        angle += GEARSystem::Angle::twoPi;
    while(angle > GEARSystem::Angle::pi)
        angle -= GEARSystem::Angle::twoPi;
    return angle;
}
