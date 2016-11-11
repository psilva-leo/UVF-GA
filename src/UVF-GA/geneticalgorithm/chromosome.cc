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

#include "chromosome.hh"

Chromosome::Chromosome(int genQty) {
    this->_genQty = genQty;
    this->_fitness = 2.0;

    // TODO: Adjust mins e maxs
    for(int i=0; i<genQty; i++) {
        genMaxs.append(1.0);
        genMins.append(0.0);
    }

    for(int i=0; i<genQty; i++) {
        Genotype temp = Genotype(genMins[i], genMaxs[i]);
        _gen.append(temp);
    }
}


int Chromosome::getGenQty() {
    return this->_genQty;
}

void Chromosome::insertGen(Genotype& gen) {
    this->_gen.append(gen);
}


double Chromosome::getFitness() {
    return this->_fitness;
//    return this->_gen.last().getValue();
}

Genotype* Chromosome::getGen(int i) {
    return &this->_gen[i];
}

/*
 * Avalia a população baseado em alguma função a ser implementada.
 * TODO: Criar função baseado nos pesos do tempo, batida e distância.
 */
void Chromosome::evaluate() {
    this->_fitness = 1.0;
}
