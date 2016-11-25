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
#include <UVF-GA/geneticalgorithm/population.hh>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define POPULATION_SIZE 10
#define MUTATION_RATE 0.5
#define MAX_ITERATIONS 10

int main(int argc, char *argv[]){
    int iteration = 1;

    // Run GA
    Population *p = new Population(POPULATION_SIZE);
    QList<Population> popList;
    srand(time(NULL));

    while(iteration < MAX_ITERATIONS) {
        cout << ">>> ITERATION " << iteration << " <<<" << endl;
        cout << "Population:" << endl;
        p->print();
        cout << "\n";

        Population crossPop = p->crossOver();
        Population mutPop = p->mutation(MUTATION_RATE);
        popList.clear();
        popList.append(crossPop);
        popList.append(mutPop);
        popList.append(*p);
        p = p->selection(popList);

        iteration++;
    }

    // Show best result
    Chromosome better = p->getBetter();


    return 0;
}
