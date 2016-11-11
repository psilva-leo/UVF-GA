#include "controlalgorithmparameters.hh"
#include <simulation/entity/player/navigation/controlalgorithm/pid/pid.hh>

ControlAlgorithmParameters::ControlAlgorithmParameters() {
    _isPidSet = false;
}

void ControlAlgorithmParameters::setPIDParameters(double kp, double ki, double kd, double iLimit) {
    _pid.kp = kp;
    _pid.ki = ki;
    _pid.kd = kd;
    _pid.iLimit = iLimit;

    _isPidSet = true;
}

void ControlAlgorithmParameters::setTo(ControlAlgorithm *ctrAlg) {
    ctrAlg->accept(this);
}

void ControlAlgorithmParameters::visit(PID *pid) {
    if(_isPidSet)
        pid->setParameters(_pid.kp, _pid.ki, _pid.kd, _pid.iLimit);
}
