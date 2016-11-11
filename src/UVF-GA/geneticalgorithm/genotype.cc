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
    this->value = 0.0;
}

Genotype::~Genotype() {
    this->min = 0.0;
    this->max = 0.0;
    this->value = 0.0;
}

Genotype::Genotype(double min, double max) {
    this->min = min;
    this->max = max;
    this->value = (double)rand()/RAND_MAX;
}

double Genotype::getValue() const {
    return this->value;
}

void Genotype::setMax(double max) {
    this->max = max;
}

void Genotype::setMin(double min) {
    this->min = min;
}

void Genotype::setValue(double x) {
    if(x > max) x = max;
    if(x < min) x = min;

    this->value = x;
}

Genotype Genotype::operator*(double nun) {
    Genotype aux(0,0);
    aux.setValue(this->value*nun);
    return aux;
}

Genotype Genotype::operator=(double num) {
    Genotype aux;
    aux.setValue(num);
    return aux;
}
