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

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <fstream>

#include <QList>
#include <sys/wait.h>

#include <UVF-GA/simulation/player/player.hh>
#include <UVF-GA/simulation/testcase/testcase.hh>

#include <3rdparty/sslworld/sslworld.hh>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define SIMULATION_STEP (1/30.0f) // seconds

#define SIMULTANEOUS_PROCESS 5


class Simulation {
public:
    Simulation();
    void run();

    // Population param
    void setPopulationParams(QList<QList<float> > params) { _params = params; }
    void setPopulationSize(int size) { _numTests = size; }

    // Get the results
    QList<QList<float> > results() { return _results; }

private:
    // Intern
    int _numTests;
    int _myId;
    QList<QList<float> > _params;
    QList<QList<float> > _results;

    // Remover depois
    Timer _timer;
    QList<pid_t> _child;

    // Max speed
    float _maxASpeed;
    float _maxLSpeed;

    // UVF params
    double _de;
    double _kr;
    double _dmin;
    double _delta;
    double _k0;

    // Angular control algorithm params
    float _akp;
    float _aki;
    float _akd;
    float _alimit;

    // Linear control algorithm params
    float _lkp;
    float _lki;
    float _lkd;
    float _llimit;
};

#endif // SIMULATION_H
