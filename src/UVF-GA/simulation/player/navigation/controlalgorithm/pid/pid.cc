#include "pid.hh"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

QString PID::name() {
    return "PID";
}

PID::PID() {
    setParameters(0.0, 0.0, 0.0, 0.0);
    reset();
}

PID::PID(float kp, float ki, float kd, float iLimit) {
    setParameters(kp, ki, kd, iLimit);
    reset();
}

PID::~PID() {

}

void PID::reset() {
    _iError = 0;
    _lastError = 0;
    _hasLastError = false;
    ControlAlgorithm::reset();
}

float PID::_iterate(float error, float dt) {
    // dt check
    if(dt > 0.250)
        std::cout << "[WARNING] " << name().toStdString() << ": Very high dt! Check cause.\n";

    // Integration, with windup guarding
    _iError += error * dt;
    if(_iError < -_iLimit) _iError = -_iLimit;
    if(_iError >  _iLimit) _iError =  _iLimit;

    // Differentiation
    float diff = _hasLastError? (error-_lastError)/dt : 0.0;

    // Scaling
    float p_term = (_kp * error);
    float i_term = (_ki * _iError);
    float d_term = (_kd * diff);

    // Save current error for next iteration
    _lastError = error;
    _hasLastError = true;

    return p_term + i_term + d_term;
}

void PID::accept(ControlAlgorithmParameters *params) {
    params->visit(this);
}

void PID::setParameters(double kp, double ki, double kd, double iLimit) {
    _kp = kp;
    _ki = ki;
    _kd = kd;
    _iLimit = iLimit;
}


