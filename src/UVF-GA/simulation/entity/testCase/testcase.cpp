#include "testcase.h"
#include <iostream>

TestCase::TestCase(){
    RobotsFomation form(2);
    FieldConfig cfg;

    _world = new SSLWorld(&cfg, &form, &form);
    _player = new Player(0, _world);
    _timer = new Timer();
}

TestCase::~TestCase() {
    delete _world;
    delete _player;
    delete _timer;
}

void TestCase::initialization() {
    _world->robots[0]->setXY(0, 0);
    _world->robots[0]->setDir(0.0);

    // Remove all other robots from field
    for(int i=1; i<2*ROBOT_COUNT; i++)
        _world->robots[i]->setXY(0.3*i, -10);
}

void TestCase::loop() {
    _player->goToLookTo(Position(-1.0, 0.0), 0, false, false);

    float ori = _player->orientation();

    dReal x, y;
    _world->robots[0]->getXY(x, y);
    std::cout << "Robot #0: X=" << x << ", Y=" << y << ", Ori=" << ori << "\n";

    _world->step(0.0050);
    QThread::msleep(10);
}

void TestCase::finalization() {

}
