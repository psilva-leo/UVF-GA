#include "testcase.hh"
#include <iostream>

TestCase::TestCase(){
    _world = new SSLWorld();
    _player = new Player(0, _world);
    _timer = new Timer();
    _reachedGoal = false;
    _msecTestTime = 0.0;

    _desiredPos = Position(0.0, 0.0);
    _desiredAngle = 0.0;
    _avoidRobots = false;
    _avoidBall = false;
}

TestCase::~TestCase() {
    delete _world;
    delete _player;
    delete _timer;
}

QString TestCase::name() {
    return "TestCase";
}

void TestCase::initialization() {
    _world->robots[0]->setXY(0, 0);
    _world->robots[0]->setDir(0.0);

    // Remove all other robots from field
    for(int i=1; i<2*ROBOT_COUNT; i++)
        _world->robots[i]->setXY(0.3*i, -10);

    // Set ball
    _world->ball->setBodyPosition(1.0, 0.0, 0.0);

    // Config player
    _player->setAngularCtrlParameters(2.0, 0.0, 0.0, 20.0);
    _player->setLinearCtrlParameters(1.5, 0.0, 0.0, 0.0);
    _player->setMaxSpeed(2.5*PI, 3.0);
    _player->setUVFParameters(0.15, 0.40, 0.005, 0.12, 1);

    // Start timer
    _timer->start();

    // Config default go to look to
    configGoToLookTo(Position(1.0, -1.0), PI/2, false, false);
}

void TestCase::loop() {
    // Updated timer
    _timer->stop();
    _msecTestTime = _timer->timemsec();

    // Check if player has reached goal
    if(_player->hasReachedGoal())
        _reachedGoal = true;

    // Go to look to
    _player->goToLookTo(_desiredPos, _desiredAngle, _avoidRobots, _avoidBall);

    // DEBUG PRINT
    float ori = _player->orientation();
    dReal x, y;
    _world->robots[0]->getXY(x, y);
    std::cout << "Robot #0: X=" << x << ", Y=" << y << ", Ori=" << ori << "\n";

    // Step world
    _world->step(0.010);
    QThread::msleep(10);
}

void TestCase::finalization() {
}

void TestCase::setLinearCtrlParameters(float kp, float ki, float kd, float limit) {
    _player->setLinearCtrlParameters(kp, ki, kd, limit);
}

void TestCase::setAngularCtrlParameters(float kp, float ki, float kd, float limit) {
    _player->setAngularCtrlParameters(kp, ki, kd, limit);
}

void TestCase::setUVFParameters(double de, double kr, double dmin, double delta, double k0) {
    _player->setUVFParameters(de, kr, dmin, delta, k0);
}

void TestCase::setMaxSpeed(float maxASpeed, float maxLSpeed) {
    _player->setMaxSpeed(maxASpeed, maxLSpeed);
}

void TestCase::configGoToLookTo(Position desiredPos, float angleToLook, bool avoidRobots, bool avoidBall) {
    _desiredPos = desiredPos;
    _desiredAngle = angleToLook;
    _avoidBall = avoidBall;
    _avoidRobots = avoidRobots;
}
