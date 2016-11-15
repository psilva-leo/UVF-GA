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

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <UVF-GA/geneticalgorithm/population.hh>
#include <time.h>

#include <QApplication>
#include <QProcess>
#include <QList>
#include <QThread>
#include <sys/wait.h>

#include <UVF-GA/simulation/player/player.hh>
#include <UVF-GA/simulation/testcase/testcase.hh>

#include <3rdparty/sslworld/sslworld.hh>
#include <3rdparty/soccerview/soccerview.hh>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define POPSIZE 10

#define SIMULATION_STEP (1/30.0f) // seconds

#define ENABLE_GRAPHICS true

#define SIMULTANEOUS_PROCESS 5

int main(int argc, char *argv[]){
//    int iteration = 1;

//    Population *P = new Population(POPSIZE);
//    QList<Population> popList;
//    srand(time(NULL));

//    while(iteration < 2){
//        cout << ">>> ITERATION " << iteration << " <<<" << endl;
//        cout << "Inital population of Iteration" << endl;
//        P->print();
//        Population crossPop = P->crossOver();
//        Population mutPop = P->mutation(0.5);
//        popList.clear();
//        popList.append(crossPop);
//        popList.append(mutPop);
//        popList.append(*P);
//        P = P->selection(popList);
//        iteration++;
//        cout << "\n\n\n\n";
//    }



//    // SoccerView
//    GLSoccerView view;
//    if(ENABLE_GRAPHICS) view.show();

//    // Loop interface
//    if(ENABLE_GRAPHICS) {
//        app.processEvents();
//        view.updateDetection(world);
//    }

//    // Close interface
//    if(ENABLE_GRAPHICS) view.close();


    QApplication app(argc, argv);

    Timer timer;
    timer.start();

    int numTests = 50;

    // Fork tests
    int myId = 0;
    QList<pid_t> child;
    for(int i=1; i<numTests; i++) {
        pid_t pid = fork();

        if(pid==0) { // children
            myId = i;
            break;
        } else { // father
            child.append(pid);

            // Limit simultaneous process
            if(child.size() >= SIMULTANEOUS_PROCESS) {
                waitpid(child.first(), NULL, 0);
                child.removeFirst();
            }

            continue;
        }
    }

    // Create test
    TestCase *test = new TestCase(100.0, SIMULATION_STEP);
    test->configMovement(Position(-2.0, 0.0), 0.0, Position(2.0, 2.0), 0, false, false);
    test->configACtrParams(2.0, 0.0, 0.0, 20.0);
    test->configLCtrParams(1.5, 0.0, 0.0, 0.0);
    test->configMaxSpeed(2.5*PI, 3.0);
    test->configUVFParams(0.15, 0.40, 0.005, 0.12, 1);

    std::cout << "Starting test case #" << myId << "...\n";
    test->start();
    test->wait();
    std::cout << "Test case #" << myId << ", run time: " << test->timesec() << " seconds (reached goal: " << test->reachedGoal() << ")\n";

    if(myId==0)
        for(int i=0; i < child.size(); i++) waitpid(child.at(i), NULL, 0);

    delete test;

    if(myId==0) {
        timer.stop();
        std::cout << "total time: " << timer.timesec() << " seconds\n";
    }

    exit(0);
}
