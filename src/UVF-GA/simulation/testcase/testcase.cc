#include "testcase.hh"
#include <iostream>

TestCase::TestCase(){
    _world = new SSLWorld();
    _player = new Player(0, _world);
    _timer = new Timer();
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
    _player->setMaxSpeedAndAccel(2.5*PI, 3.0, 1.35);
    _player->setUVFParameters(0.15, 0.40, 0.005, 0.12, 1);
}

void TestCase::loop() {
    _player->goToLookTo(Position(-1.0, 0.0), 0, false, false);

    float ori = _player->orientation();

    dReal x, y;
    _world->robots[0]->getXY(x, y);
    std::cout << "Robot #0: X=" << x << ", Y=" << y << ", Ori=" << ori << "\n";

    _world->step(0.010);
    QThread::msleep(10);
}

void TestCase::finalization() {
}
