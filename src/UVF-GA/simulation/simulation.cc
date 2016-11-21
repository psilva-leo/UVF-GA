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

#include "simulation.hh"
#include <cstdio>
#include <unistd.h>

Simulation::Simulation() {
    _numTests = 10;
    _myId = 0;
}

void Simulation::run() {
    _timer.start();

    // Fork tests
    for(int i=1; i<_numTests; i++) {
        pid_t pid = fork();

        if(pid==0) { // children
            _myId = i;
            break;
        } else {     // father
            // Append child's pid to the fathers list
            _child.append(pid);

            // Limit simultaneous process
            if(_child.size() >= SIMULTANEOUS_PROCESS) {
                waitpid(_child.first(), NULL, 0);
                _child.removeFirst();
            }

            // When there is less the SIMULTANEOUS_PROCESS childrens
            continue;
        }
    }

    // Create test
    TestCase *test = new TestCase(100.0, SIMULATION_STEP);

    // Config movement
    test->configMovement(Position(-2.0, 0.0), 0.0, Position(2.0, 2.0), 0, false, false);

    // Config angular controller
    test->configACtrParams(2.0, 0.0, 0.0, 20.0);

    // Config angular controller
    test->configLCtrParams(1.5, 0.0, 0.0, 0.0);

    // Config max speeds
    if(_speedParams.size()-1 >= _myId) {
        test->configMaxSpeed(_speedParams.at(_myId)->maxASpeed, _speedParams.at(_myId)->maxLSpeed);
    } else {
        test->configMaxSpeed(2.5*PI, 3.0);
        std::cout << "[WARNING] Speed constants not set, using default values" << std::endl;
    }

    // Config UVF
    if(_UVFParams.size()-1 >= _myId) {
        test->configUVFParams(_UVFParams.at(_myId)->de,_UVFParams.at(_myId)->kr,
                              _UVFParams.at(_myId)->dmin,_UVFParams.at(_myId)->delta,
                              _UVFParams.at(_myId)->k0);
    } else  { // Use default values
        test->configUVFParams(0.15, 0.40, 0.005, 0.12, 1);
        std::cout << "[WARNING] UVF constants not set, using default values" << std::endl;
    }

    // Starting case
    std::cout << "Starting test case #" << _myId << "...\n";
    test->start();
    test->wait();

    // Waiting for the childrens to end
    if(_myId==0) for(int i=0; i < _child.size(); i++) waitpid(_child.at(i), NULL, 0);

    // Simulation time
    if(_myId==0) {
        _timer.stop();
        std::cout << "total time: " << _timer.timesec() << " seconds\n";
    }

    // Comunication process
    if(_myId == 0){ // Read
        // Write my results
        struct Results *myResults = new Results;
        myResults->time = test->timesec();
        myResults->reachedGoal = test->reachedGoal();

        _results.append(myResults);

        for(int i=1; i < _numTests; i++) {
            // Configuring file name
            char fileName[18] = "testecase000.txt\0";
            int unit    = i%10;
            int ten     = ((i%100) - unit)/10;
            int hundred = (i-unit-10*ten)/100;

            fileName[9]  += hundred;
            fileName[10] += ten;
            fileName[11] += unit;

            // Open file
            std::ifstream myfile(fileName, std::ios_base::in);

            // Get message and print
            struct Results *childResult = new Results;
            myfile >> childResult->time >> childResult->reachedGoal;
            std::cout << "Message from the child #" << i << ": " << childResult->time << " "
                      << childResult->reachedGoal << std::endl;

            // Write child result
            _results.append(childResult);

            // Close and remove file
            myfile.close();
            remove(fileName);
        }

    } else {       // Write

        // Configure file name
        int tmp = _myId;
        char fileName[18] = "testecase000.txt\0";
        while(tmp >= 100) { fileName[9]++ ; tmp -=100; }
        while(tmp >=  10) { fileName[10]++; tmp -= 10; }
        while(tmp >=   1) { fileName[11]++; tmp -=  1; }

        // Open file
        std::ofstream myfile;
        myfile.open(fileName);

        // Struct
        struct Results *myResults = new Results;
        myResults->time = test->timesec();
        myResults->reachedGoal = test->reachedGoal();

        // Write
        myfile << myResults->time << ' ' << myResults->reachedGoal;

        // Close file
        myfile.close();
    }

    // Delete teste case
    delete test;

    // Exit if child
    if(_myId != 0) exit(0);
}
