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
private:
    int _numTests;
    int _myId;
    QList<pid_t> _child;

    Timer _timer;

};

#endif // SIMULATION_H
