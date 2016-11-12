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

#include "navigationalgorithm.hh"

#define NAVALG_MAXTIME 5 // ms

NavigationAlgorithm::NavigationAlgorithm() {

}

NavigationAlgorithm::~NavigationAlgorithm() {

}

void NavigationAlgorithm::runNavigationAlgorithm() {
    // Run NavigationAlgorithm specific implementation
    run();
}

void NavigationAlgorithm::setOrigin(const Position &pos, const float &ori) {
    _originPos = pos;
    _originOri = ori;
}

void NavigationAlgorithm::setGoal(const Position &pos, const float &ori) {
    _goalPos = pos;
    _goalOri = ori;
}

float NavigationAlgorithm::getDistance() const {
//    QMutexLocker locker(&_pathMutex);
//    return _distance;
    return sqrt(pow(_goalPos.x()-_originPos.x(),2)+pow(_goalPos.y()-_originPos.y(), 2));
}

//QLinkedList<Position> NavigationAlgorithm::getPath() const {
//    QMutexLocker locker(&_pathMutex);

//    // Return path
//    return _path;
//}

