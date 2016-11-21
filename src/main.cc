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
#include <fstream>
#include <UVF-GA/geneticalgorithm/population.hh>
#include <time.h>

#include <QApplication>
#include <QProcess>
#include <QList>
#include <QThread>
#include <sys/wait.h>

#include <UVF-GA/simulation/player/player.hh>
#include <UVF-GA/simulation/testcase/testcase.hh>
#include <UVF-GA/simulation/simulation.hh>

#include <3rdparty/sslworld/sslworld.hh>
#include <3rdparty/soccerview/soccerview.hh>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define POPSIZE 15

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

///   // SoccerView
//    GLSoccerView view;
//    if(ENABLE_GRAPHICS) view.show();

//    // Loop interface
//    if(ENABLE_GRAPHICS) {
//        app.processEvents();
//        view.updateDetection(world);
//    }

//    // Close interface
//    if(ENABLE_GRAPHICS) view.close();

//    QApplication app(argc, argv);

    // Paramets example
    QList<QList<float> > popParams;
    for(int i = 0; i < POPSIZE; i++) {
        QList<float> specimen;
        specimen.append(0.150);
        specimen.append(0.400);
        specimen.append(0.005);
        specimen.append(0.120);
        specimen.append(1.000);
        popParams.append(specimen);
    }

    // Simulate one pop
    Simulation *simul = new Simulation();
    simul->setPopulationSize(POPSIZE);
    simul->setPopulationParams(popParams);
    simul->run();
    QList<QList<float> > results = simul->results();
    delete simul;

    return 0;
}
