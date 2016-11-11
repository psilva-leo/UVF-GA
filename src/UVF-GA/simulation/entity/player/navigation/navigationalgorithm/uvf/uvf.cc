#include "uvf.hh"

UVF::UVF() {
    _de = 0.07;
    _kr = 0.05;
    _dmin  = 0.005;
    _delta = 0.12;
    _k0 = 1;

    reset();
}

UVF::~UVF() {

}

void UVF::reset() {
    _resultantDirection = 0.0;
    _obstacles.clear();
}

void UVF::setParameters(double de, double kr, double dmin, double delta, double k0) {
    _de = de;
    _kr = kr;
    _dmin = dmin;
    _delta = delta;
    _k0 = k0;
}

void UVF::addBall(const Position &pos, const Velocity &vel) {
    addObstacle(pos, vel);
}

void UVF::addRobot(const Position &pos, const Velocity &vel) {
    addObstacle(pos, vel);
}

float UVF::getDirection() const {
    return _resultantDirection;
}

Position UVF::rotate(const Position &pos, float rot){
    return Position(pos.x()*cos(rot) - pos.y()*sin(rot), pos.x()*sin(rot) + pos.y()*cos(rot));
}

Velocity UVF::rotate(const Velocity &vel, float rot) {
    return Velocity(vel.x()*cos(rot) - vel.y()*sin(rot), vel.x()*sin(rot) + vel.y()*cos(rot));
}

float UVF::getPhiTUF(float x, float y, float de){
    float yL = y + de;
    float yR = y - de;
    Position pL(x, yL);
    Position pR(x, yR);

    if(y < -de) {
        return getPhi(pL, true, de);

    } else if(y >= de) {
        return getPhi(pR, false, de);

    } else {
        float phiHCCW = getPhi(pR, false, de);
        float phiHCW = getPhi(pL, true, de);

        Position NhCW (cos(phiHCW) , sin(phiHCW) );
        Position NhCCW(cos(phiHCCW), sin(phiHCCW));

        float phiX = ((fabs(yL)*NhCCW.x()) + (fabs(yR)*NhCW.x()))/(2*de);
        float phiY = ((fabs(yL)*NhCCW.y()) + (fabs(yR)*NhCW.y()))/(2*de);

        return atan2(phiY, phiX);
    }
}

float UVF::mergeVF(const Position &auf, float phiAUF, float phiTUF, Position tmpObst, Position tmpGoalPos){
    float phi;

    float dmin = _dmin;
    float r = sqrt(pow(auf.x(), 2) + pow(auf.y(), 2));
    if(r <= dmin) {
        phi = phiAUF;

    } else {
        // Merge
        float g = gauss(r-dmin);
        float diff = fabs(phiAUF - phiTUF);
        if(diff > PI)
            diff = fabs(2*PI - diff);

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
        Position vecObst(tmpObst.x() - tmpGoalPos.x(), tmpObst.y() - tmpGoalPos.y());
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
//    if(originPos().isUnknown() || goalPos().isUnknown() || goalOri().isUnknown()) {
//        std::cout << "[WARNING] UVF: originPos, goalPos or goalOri is unknown!\n";
//        return;
//    }

    float targetOri = goalOri() + PI;

    // Get rotation
    float rot = wrapToPi(targetOri);
    rot = PI - rot;

    Position tmpOriginPos = rotate(originPos(), rot);
    Position tmpGoalPos = rotate(goalPos(), rot);

    // Translate x-y axis
    float x = tmpOriginPos.x() - tmpGoalPos.x();
    float y = tmpOriginPos.y() - tmpGoalPos.y();

    // Iterate through obstacles
    float phi = 0.0;

    // Calculate phiTUF
    float phiTUF = getPhiTUF(x, y, _de);

    for(int i=0; i<_obstacles.size(); i++) { // Traverse through QList
        UVFObstacle obst = _obstacles.at(i);

        // Fetch obstacle and rotate
        Velocity tmpObstVel = rotate(obst.velocity(), rot);
        Position tmpObstPos = rotate(obst.virtualPosition(tmpObstPos, tmpObstVel), rot);

        // Calculate distance
        float tmpDistance = sqrt(pow(tmpObstPos.x()-tmpGoalPos.x(), 2) + pow(tmpObstPos.y()-tmpGoalPos.y(), 2));

        // Obstacle close to goal position exception
        if(tmpDistance < 0.10)
            continue;

        // Calculate phiAUF
        Position auf(tmpOriginPos.x() - tmpObstPos.x(), tmpOriginPos.y() - tmpObstPos.y());
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
    _resultantDirection = (phi-rot);
}

void UVF::addObstacle(const Position &pos, const Velocity &vel) {
    _obstacles.append(UVFObstacle(pos, vel));
}

float UVF::getPhi(const Position &p, bool ccw, float de) const {
    float kr = _kr;

    float signal = (ccw? -1.0 : 1.0);
    float theta = atan2(p.y(), p.x());
    float ro = sqrt(pow(p.x(), 2) + pow(p.y(), 2));
    if(ro > de)
        return theta + signal*(PI/2.0)*(2.0-(de+kr)/(ro+kr));
    else
        return theta + signal*(PI/2.0)*sqrt(ro/de);
}

float UVF::gauss(float r) const {
    float delta = _delta;
    return exp(-(pow(r,2))/(2*pow(delta,2)));
}

float UVF::wrapToPi(float angle) {
    while(angle < -PI)
        angle += 2*PI;
    while(angle > PI)
        angle -= 2*PI;
    return angle;
}
