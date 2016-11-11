#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <UVF-GA/geneticalgorithm/population.h>
#include <time.h>

#include <QApplication>
#include <QList>
#include <QThread>

#include <UVF-GA/simulation/entity/player/player.h>

#include <3rdparty/sslworld/sslworld.h>
#include <3rdparty/soccerview/soccerview.hh>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define POPSIZE 10

#define SIMULATION_PERIOD 0.020 // seconds
#define RUN_PERIOD 0.020 // seconds

int main(int argc, char *argv[]){
//    //if(argc < 2){return -1;}
//    //Population P = new Population(argv[1]);

//    Population P = Population(POPSIZE);

//    srand(time(NULL));

//    P.generate();
//    P.print();
//    QList<Population> pop;
//    pop.append(P);
//    P.selection(pop);

//    P.crossOver();

//    P.mutation(0.5);

//    seleciona(inicial) => selecionados (x elementos)

//    crossover(selecionados) => pop_atual1

//    mutação(pop_atual1)   => pop_atual2

//    evaluation()

//    seleciona(selecionados, pop_atual2) (x elementos)


    QApplication app(argc, argv);

    // SoccerView
    GLSoccerView view;
    view.show();

    // Create SSLWorld
    RobotsFomation *form = new RobotsFomation(2);
    FieldConfig *cfg = new FieldConfig();
    SSLWorld *world = new SSLWorld(cfg, form, form);

    // Create player
    Player *player = new Player(0, world);

    // Set test robot initial position
    world->robots[0]->setXY(-2.0, 0);
    world->robots[0]->setDir(0.0);

    // Remove all other robots from field
    for(int i=1; i<2*ROBOT_COUNT; i++)
        world->robots[i]->setXY(0.3*i, -3.25);

    // Set ball
    world->ball->setBodyPosition(1.0, 0.0, 0.0);

    Timer timer;
    forever {
        timer.start();

        // Process app events
        app.processEvents();

        // Set player destination
        Position desiredPos(2.5, -1.0);
        player->goToLookTo(desiredPos, -PI, false);

        // Print player info
//        Position pos = player->position();
//        float ori = player->orientation();
//        std::cout << "Robot #0: X=" << pos.x() << ", Y=" << pos.y() << ", Ori=" << ori << "\n";

        // Step world
        world->step(SIMULATION_PERIOD);

        // Sleep run period
        timer.stop();
        float rest = RUN_PERIOD*1000 - timer.timemsec();
        if(rest > 0)
            QThread::msleep(rest);

        // Update view
        view.updateDetection(world);
    }

    // Deletes
    delete world;
    delete cfg;
    delete form;

    return 0;
}
