#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <fstream>

#include <QList>
#include <sys/wait.h>

#include <UVF-GA/simulation/player/player.hh>
#include <UVF-GA/simulation/testcase/testcase.hh>

#include <3rdparty/sslworld/sslworld.hh>
#include <3rdparty/soccerview/soccerview.hh>

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
