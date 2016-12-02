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

#include <iostream>
#include <QApplication>
#include <UVF-GA/geneticalgorithm/population.hh>
#include <3rdparty/soccerview/soccerview.hh>
#include <UVF-GA/simulation/testcase/testcase.hh>
# include <time.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define POPULATION_SIZE 15
#define MUTATION_RATE 0.5
#define CROSSOVER_RATE 0.5
#define MAX_ITERATIONS 20
#define OLD_POP_SLECTION_RATE 0.3

#define VIEW_STEP (1/60.0f) // seconds

int main(int argc, char *argv[]){
    srand(time(NULL));
    int iteration = 1;

    time_t start;
    time(&start);

    // Run GA
    cout << "Generating initial random population...\n";
    Population *pop = new Population(POPULATION_SIZE);

    cout << "Evaluating initial population...\n\n";
    pop->evaluate();

    QList<Population> popList;
    while(iteration <= MAX_ITERATIONS) {
        cout << ">>> ITERATION " << iteration << " <<<" << endl;
        pop->print();
        cout << "\n";

        Population crossPop = pop->crossOver(CROSSOVER_RATE);
        Population mutPop = crossPop.mutation(MUTATION_RATE);
        popList.clear();
        popList.append(crossPop);
        popList.append(mutPop);
//        Population selectoin_old = pop->selection_old(OLD_POP_SLECTION_RATE*POPULATION_SIZE);
//        popList.append(selectoin_old);
        pop = pop->selection(popList);

        iteration++;
    }

    // Last Population
    cout << "\n Last Population" << endl;
    pop->print();

    // Get better result
    Chromosome *better = pop->getBetter();
    double de    = better->getGen(0)->getValue();
    double kr    = better->getGen(1)->getValue();
    double dmin  = better->getGen(2)->getValue();
    double delta = better->getGen(3)->getValue();
    double k0    = better->getGen(4)->getValue();
    double maxASpeed = better->getGen(5)->getValue();
    double maxLSpeed = better->getGen(6)->getValue();

    // Print
    cout << "de: " << de << "\nkr: " << kr << "\ndmin: " << dmin << "\ndelta: " << delta << "\nk0: " << k0 << "\nmaxASpeed: " << maxASpeed << "\nmaxLSpeed: " << maxLSpeed << endl;
    cout << "Fitness: " << better->getFitness() << endl;
    time_t end;
    time(&end);
    cout << "\n>>Execution time: " << ((double) (end - start))/60 << " min" << endl;

    // Create test case with better result
    TestCase test(10.0, VIEW_STEP);
    test.configUVFParams(de, kr, dmin, delta, k0);
    test.configMaxSpeed(maxASpeed, maxLSpeed);

    test.configMovement(Position(-2.5, -1.3), Utils::toRad(120), Position(2.75, 1.75), Utils::toRad(90), true, true);
    test.configACtrParams(2.0, 0.0, 0.0, 20.0);
    test.configLCtrParams(1.5, 0.0, 0.0, 0.0);

    // Get access to player and world
    Player *player = test.player();
    SSLWorld *world = test.world();

    // Run view
    QApplication app(argc, argv);
    GLSoccerView view;
    view.show();

    test.initialize();
    while(player->hasReachedGoal()==false) {
        app.processEvents();
        view.updateDetection(world);

        test.iterate(VIEW_STEP);
        QThread::msleep(VIEW_STEP*1E3f);
    }
    test.finalize();

    // Stop
    app.exec();

    // Close interface
    view.close();

    return 0;
}
