#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <UVF-GA/geneticalgorithm/population.h>
#include <time.h>
#include <QList>
#include <QThread>

#include <3rdparty/sslworld/sslworld.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define POPSIZE 10

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





    // SSL World testing
//    RobotsFomation *form = new RobotsFomation(2);
//    FieldConfig *cfg = new FieldConfig();
//    SSLWorld *ssl = new SSLWorld(cfg, form, form);

//    ssl->robots[0]->setXY(0, 0);
//    ssl->robots[0]->setDir(3.14/2);

//    forever {
//        ssl->robots[0]->setSpeed(0.0, 1.0, 0.0);

//        dReal x, y;
//        ssl->robots[0]->getXY(x, y);
//        std::cout << "robot 0, x=" << x << ", y=" << y << "\n";

//        ssl->step(0.02);
//        QThread::msleep(20);
//    }

//    delete ssl;
//    delete cfg;
//    delete form;


    return 0;
}
