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

#include "genotype.hh"
#include <cstdlib>

Genotype::Genotype() {
    this->_value = 0.0;
}

Genotype::~Genotype() {
    this->_min = 0.0;
    this->_max = 0.0;
    this->_value = 0.0;
}

Genotype::Genotype(double min, double max) {
    this->_min = min;
    this->_max = max;
    this->_value = (double)rand()/RAND_MAX;
}

double Genotype::getValue() const {
    return this->_value;
}

void Genotype::setMax(double max) {
    this->_max = max;
}

void Genotype::setMin(double min) {
    this->_min = min;
}

void Genotype::setValue(double x) {
    if(x > _max) x = _max;
    if(x < _min) x = _min;

    this->_value = x;
}

Genotype Genotype::operator*(double nun) {
    Genotype aux(0,0);
    aux.setValue(this->_value*nun);
    return aux;
}

Genotype Genotype::operator=(double num) {
    Genotype aux;
    aux.setValue(num);
    return aux;
}
