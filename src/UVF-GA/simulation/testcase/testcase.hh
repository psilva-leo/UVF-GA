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

#ifndef TESTCASE_H
#define TESTCASE_H

#include <UVF-GA/utils/entity/entity.hh>
#include <UVF-GA/simulation/player/player.hh>
#include <UVF-GA/utils/utils.hh>
#include <3rdparty/sslworld/sslworld.hh>

class TestCase : public Entity {
public:
    TestCase();
    ~TestCase();

private:
    SSLWorld *_world;
    Player *_player;
    Timer *_timer;

    void initialization();
    void loop();
    void finalization();
};

#endif // TESTCASE_H