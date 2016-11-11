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
#include <cstdlib>
#include <iostream>
#include <UVF-GA/geneticalgorithm/population.hh>
#include <time.h>

#include <QApplication>
#include <QList>
#include <QThread>

#include <UVF-GA/simulation/player/player.hh>

#include <3rdparty/sslworld/sslworld.hh>
#include <3rdparty/soccerview/soccerview.hh>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define POPSIZE 10

#define SIMULATION_PERIOD 0.033 // seconds
#define RUN_PERIOD 0.0 // seconds

#define ENABLE_GRAPHICS true

int main(int argc, char *argv[]){
//    int iteration = 0;

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

//    seleciona(inicial) => selecionados (x elementos)

//    crossover(selecionados) => pop_atual1

//    mutação(pop_atual1)   => pop_atual2

//    evaluation()

//    seleciona(selecionados, pop_atual2) (x elementos)


    QApplication app(argc, argv);

    // SoccerView
    GLSoccerView view;
    if(ENABLE_GRAPHICS) view.show();

    // Create SSLWorld
    RobotsFomation *form = new RobotsFomation(2);
    FieldConfig *cfg = new FieldConfig();
    SSLWorld *world = new SSLWorld(cfg, form, form);

    // Create player
    Player *player = new Player(0, world);

    // Set test robot initial position
    world->robots[0]->setXY(-2.0, 0);
    world->robots[0]->setDir(90.0);

    // Remove all other robots from field
    for(int i=1; i<2*ROBOT_COUNT; i++)
        world->robots[i]->setXY(0.3*i, -3.25);

    // Set ball
    world->ball->setBodyPosition(1.0, 0.0, 0.0);

    Timer timer;
    forever {
        timer.start();

        // Process app events
        if(ENABLE_GRAPHICS) app.processEvents();

        // Set player destination
        Position desiredPos(-2.5, -1.0);
        player->goToLookTo(desiredPos, -PI/2, false, false);

        // Step world
        world->step(SIMULATION_PERIOD);

        // Update view
        if(ENABLE_GRAPHICS) view.updateDetection(world);

        timer.stop();

        // Sleep run period
        if(RUN_PERIOD!=0.0f) {
            float rest = RUN_PERIOD*1E3 - timer.timemsec();
            if(rest > 0)
                QThread::msleep(rest);
            else
                std::cout << "[TIMER OVEREXTENDED] Time: " << -rest << " ms\n";
        }
    }

    // Close interface
    if(ENABLE_GRAPHICS) view.close();

    // Deletes
    delete world;
    delete cfg;
    delete form;

    return 0;
}
