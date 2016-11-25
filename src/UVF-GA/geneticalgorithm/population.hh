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

#ifndef POPULATION_H
#define POPULATION_H

#define FRAND_PRECISION 5
#define MUT_MAX_LIMIT 2.5
#define MUT_MIN_LIMIT -2.0

#define GEN_SIZE 7

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "chromosome.hh"
#include "genotype.hh"
#include <UVF-GA/utils/utils.hh>

using namespace std;

class Population{
public:
    Population(int size);

    // Genetic Functions
    void evaluate();
    Population crossOver();
    Population mutation(float tax);
    Population* selection(QList<Population> populations);

    // Other Functins
    void appendChromosome(Chromosome newElement);
    void insertChromosome(Chromosome& newChromosome, int& position);
    Chromosome* getChromosome(int index);
    void print();

    // Return better
    Chromosome* getBetter() const { return _better; }

private:
    int _size;                   /* Population Length */
    Chromosome *_better;             /* Better Individual of Population */
    QList<Chromosome> _pop;

};

#endif // POPULATION_H
