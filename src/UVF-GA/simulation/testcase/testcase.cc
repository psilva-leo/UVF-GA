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

#include "testcase.hh"
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
