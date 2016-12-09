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
#include <fstream>
#include <QApplication>
#include <UVF-GA/geneticalgorithm/population.hh>
#include <3rdparty/soccerview/soccerview.hh>
#include <UVF-GA/simulation/testcase/testcase.hh>
#include <time.h>
#include <UVF-GA/visualizator.hh>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define POPULATION_SIZE 15
#define MUTATION_RATE 0.6
#define CROSSOVER_RATE 0.5
#define MAX_ITERATIONS 1000
#define OLD_POP_SLECTION_RATE 0.05

#define VIEW_STEP (1/60.0f) // seconds

void runView(QApplication *app, double de, double kr, double dmin, double delta, double maxASpeed, double maxLSpeed) {
    // Visualize better result on SoccerView
    GLSoccerView soccerView;
    Visualizator *view = new Visualizator(&soccerView);
    view->configMovement(Position(-2.5, -1.3), Utils::toRad(120), Position(2.75, 1.75), Utils::toRad(90), true, true);
    view->configUVFParams(de, kr, dmin, delta);
    view->configMaxSpeed(maxASpeed, maxLSpeed);
    view->configACtrParams(3.0, 0.0, 0.0, 20.0);
    view->configLCtrParams(2.0, 0.0, 0.0, 0.0);

    Timer timer;
    timer.start();
    view->start();
    soccerView.show();
    while(view->wait(1)==false) {
        app->processEvents();
        QThread::msleep(5);

        timer.stop();
        if(timer.timesec()>15)
            break;
    }
    soccerView.close();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Check arguments
    if(argc < 3) {
        std::cout << "Usage: ./UVF-GA <mode> <better-file>\n\n";
        return EXIT_FAILURE;
    }

    // Parse arguments
    const int mode = atoi(argv[1]);
    const std::string betterFilename = argv[2];

    // Switch mode
    switch(mode) {
        default:
        case 0: { // run GA
            // Randomization
            srand(time(NULL));

            // Measure time
            time_t start;
            time(&start);

            // Create initial population
            cout << "Generating initial random population...\n";
            Population *pop = new Population(POPULATION_SIZE);

            // Evaluate initial population
            cout << "Evaluating initial population...\n\n";
            pop->evaluate();

            // Open file to save better
            std::fstream betterFile(betterFilename, std::ios_base::out | std::ios_base::trunc);
            if(betterFile.is_open()==false) {
                std::cout << "Error: failed to open file '" << betterFilename << "'.\n";
                return EXIT_FAILURE;
            }

            // Run iterations
            int iteration = 1;
            QList<Population> popList;
            while(iteration <= MAX_ITERATIONS) {
                cout << ">>> ITERATION " << iteration << " <<<" << endl;
                pop->print();

                // Clear list
                popList.clear();

                // Crossover
                std::cout << "Running crossover...\n";
                Population crossPop = pop->crossOver(CROSSOVER_RATE);
                popList.append(crossPop);

                // Mutation
                std::cout << "Running mutation...\n";
                Population mutPop = crossPop.mutation(MUTATION_RATE);
                popList.append(mutPop);

                // Selection
                std::cout << "Running selection...\n";
                Population selection_old = pop->selection_old(OLD_POP_SLECTION_RATE*POPULATION_SIZE);
                popList.append(selection_old);
                pop = pop->selection(popList);

                // Save better
                Chromosome *better = pop->getBetter();
                double de    = better->getGen(0)->getValue();
                double kr    = better->getGen(1)->getValue();
                double dmin  = better->getGen(2)->getValue();
                double delta = better->getGen(3)->getValue();
                double maxASpeed = better->getGen(4)->getValue();
                double maxLSpeed = better->getGen(5)->getValue();
                betterFile.clear();
                betterFile.seekg(0, std::ios::beg);
                betterFile << de << " " << kr << " " << dmin << " " << delta << " " << maxASpeed << " " << maxLSpeed << " " << better->getFitness() << "\n";
                betterFile.flush();

                // Inc iteration
                iteration++;
            }

            betterFile.close();

            // Last Population
            cout << "\n Last Population" << endl;
            pop->print();

            // Get better result
            Chromosome *better = pop->getBetter();
            double de    = better->getGen(0)->getValue();
            double kr    = better->getGen(1)->getValue();
            double dmin  = better->getGen(2)->getValue();
            double delta = better->getGen(3)->getValue();
            double maxASpeed = better->getGen(4)->getValue();
            double maxLSpeed = better->getGen(5)->getValue();

            // Print better and execution time
            cout << "de: " << de << "\nkr: " << kr << "\ndmin: " << dmin << "\ndelta: " << delta << "\nmaxASpeed: " << maxASpeed << "\nmaxLSpeed: " << maxLSpeed << endl;
            cout << "Fitness: " << better->getFitness() << endl;
            time_t end;
            time(&end);
            cout << "\n>>Execution time: " << ((double) (end - start))/60 << " min" << endl;

            // Run view
            runView(&app, de, kr, dmin, delta, maxASpeed, maxLSpeed);

        } break;

        case 1: { // visualize last better

            // Open file
            std::fstream betterFile(betterFilename, std::ios_base::in);
            if(betterFile.is_open()==false) {
                std::cout << "Error: failed to open file '" << betterFilename << "'.\n";
                return EXIT_FAILURE;
            }

            // Read from file
            double de=0, kr=0, dmin=0, delta=0, maxASpeed=0, maxLSpeed=0, fitness=0;
            betterFile >> de >> kr >> dmin >> delta >> maxASpeed >> maxLSpeed >> fitness;
            betterFile.close();

            // Print
            cout << "de: " << de << "\nkr: " << kr << "\ndmin: " << dmin << "\ndelta: " << delta << "\nmaxASpeed: " << maxASpeed << "\nmaxLSpeed: " << maxLSpeed << "\nFitness: " << fitness << endl;

            // Run view
            runView(&app, de, kr, dmin, delta, maxASpeed, maxLSpeed);


        } break;
    }

    return 0;
}
