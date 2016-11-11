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

#include "entity.hh"
#include <iostream>
#include <UVF-GA/utils/utils.hh>

int Entity::_idcont = 0;

Entity::Entity() {
    _id = _idcont;
    _idcont++;

    _enabled = _running = true; // set running and enabled by default
    _loopTime = 1000;
}

void Entity::run() {
    initialization();

    Timer t;
    while(isRunning())	{
        t.start();
        if(isEnabled())
            loop();
        t.stop();

        if(isRunning()) {
            long rest = loopTime() - t.timemsec();
            if(rest >= 0)
                msleep(rest);
            else
                std::cout << "[TIMER OVEREXTENDED] " << name().toStdString() << " for " <<  -rest  << " ms.\n";
        }
    }

    finalization();
}

void Entity::enable(bool value) {
    _mutexEnabled.lock();
    _enabled = value;
    _mutexEnabled.unlock();
}

bool Entity::isEnabled() {
    bool result;

    _mutexEnabled.lock();
    result = _enabled;
    _mutexEnabled.unlock();

    return result;
}

bool Entity::isRunning() {
    bool result;

    _mutexRunning.lock();
    result = _running;
    _mutexRunning.unlock();

    return result;
}

void Entity::stopEntity() {
    _mutexRunning.lock();
    _running = false;
    _mutexRunning.unlock();
}

void Entity::setEntityPriority(int p) {
	_mutexPriority.lock();
	_priority = p;
	_mutexPriority.unlock();
}

int Entity::entityPriority() {
	int result;
	_mutexPriority.lock();
	result = _priority;
	_mutexPriority.unlock();
	return result;
}

void Entity::setLoopTime(float t) {
    _mutexLoopTime.lock();
    _loopTime = t;
    _mutexLoopTime.unlock();
}

void Entity::setLoopFrequency(int hz) {
    _mutexLoopTime.lock();
    if(hz!=0)
        _loopTime = 1000/hz;
    _mutexLoopTime.unlock();
}

float Entity::loopTime() {
	int result;
    _mutexLoopTime.lock();
    result =_loopTime;
    _mutexLoopTime.unlock();

	return result;
}
