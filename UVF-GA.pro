#
# SSC0713 - Sistemas Evolutivos Aplicados à Robótica
# University of Sao Paulo (USP) at Sao Carlos
#
# Autores:
# Guilherme Caixeta de Oliveira
# Anderson Hiroshi de Siqueira
# Leonardo Claudio de Paula e Silva
# Lucas dos Santos Luchiari
# Franco Saraiva
#
# This file is part of UVF-GA project.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# Application info
TEMPLATE = app
DESTDIR = bin
TARGET = UVF-GA
VERSION = 1.0
CONFIG -= c++11

# Qt config
CONFIG += console
CONFIG -= app_bundle
QT += core gui widgets opengl

# Flags
QMAKE_LFLAGS += -Wall
QMAKE_CXXFLAGS  -= -O -O1
QMAKE_CXXFLAGS  += -O2 -ansi -Wall

# Libs
LIBS += -lode -lGLU

# Temporary dirs
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/moc
RCC_DIR = tmp/rc

# Source files
INCLUDEPATH *= . src

SOURCES += \
    src/3rdparty/soccerview/util/field.cc \
    src/3rdparty/soccerview/gltext.cc \
    src/3rdparty/soccerview/soccerview.cc \
    src/3rdparty/sslworld/physics/pball.cc \
    src/3rdparty/sslworld/physics/pbox.cc \
    src/3rdparty/sslworld/physics/pcylinder.cc \
    src/3rdparty/sslworld/physics/pfixedbox.cc \
    src/3rdparty/sslworld/physics/pground.cc \
    src/3rdparty/sslworld/physics/pobject.cc \
    src/3rdparty/sslworld/physics/pray.cc \
    src/3rdparty/sslworld/physics/pworld.cc \
    src/3rdparty/sslworld/fieldconfig.cc \
    src/3rdparty/sslworld/robot.cc \
    src/3rdparty/sslworld/sslworld.cc \
    src/UVF-GA/geneticalgorithm/chromosome.cc \
    src/UVF-GA/geneticalgorithm/genotype.cc \
    src/UVF-GA/geneticalgorithm/population.cc \
    src/UVF-GA/simulation/player/navigation/controlalgorithm/pid/pid.cc \
    src/UVF-GA/simulation/player/navigation/controlalgorithm/controlalgorithm.cc \
    src/UVF-GA/simulation/player/navigation/controlalgorithm/controlalgorithmparameters.cc \
    src/UVF-GA/simulation/player/navigation/navigationalgorithm/uvf/uvf.cc \
    src/UVF-GA/simulation/player/navigation/navigationalgorithm/uvf/uvfobstacle.cc \
    src/UVF-GA/simulation/player/navigation/navigationalgorithm/navigationalgorithm.cc \
    src/UVF-GA/simulation/player/navigation/navigation.cc \
    src/UVF-GA/simulation/player/player.cc \
    src/UVF-GA/simulation/testcase/testcase.cc \
    src/UVF-GA/utils/entity/entity.cc \
    src/UVF-GA/utils/position/position.cc \
    src/UVF-GA/utils/timer/timer.cc \
    src/UVF-GA/utils/velocity/velocity.cc \
    src/UVF-GA/utils/utils.cc \
    src/main.cc \
    src/UVF-GA/simulation/simulation.cc

# Header files
HEADERS += \
    src/3rdparty/soccerview/util/field.hh \
    src/3rdparty/soccerview/util/field_default_constants.hh \
    src/3rdparty/soccerview/util/geometry.hh \
    src/3rdparty/soccerview/util/gvector.hh \
    src/3rdparty/soccerview/util/timer.hh \
    src/3rdparty/soccerview/util/util.hh \
    src/3rdparty/soccerview/gltext.hh \
    src/3rdparty/soccerview/soccerview.hh \
    src/3rdparty/sslworld/physics/pball.hh \
    src/3rdparty/sslworld/physics/pbox.hh \
    src/3rdparty/sslworld/physics/pcylinder.hh \
    src/3rdparty/sslworld/physics/pfixedbox.hh \
    src/3rdparty/sslworld/physics/pground.hh \
    src/3rdparty/sslworld/physics/pobject.h \
    src/3rdparty/sslworld/physics/pray.hh \
    src/3rdparty/sslworld/physics/pworld.hh \
    src/3rdparty/sslworld/fieldconfig.hh \
    src/3rdparty/sslworld/robot.hh \
    src/3rdparty/sslworld/sslworld.hh \
    src/UVF-GA/geneticalgorithm/chromosome.hh \
    src/UVF-GA/geneticalgorithm/genotype.hh \
    src/UVF-GA/geneticalgorithm/population.hh \
    src/UVF-GA/simulation/player/navigation/controlalgorithm/pid/pid.hh \
    src/UVF-GA/simulation/player/navigation/controlalgorithm/controlalgorithm.hh \
    src/UVF-GA/simulation/player/navigation/controlalgorithm/controlalgorithmparameters.hh \
    src/UVF-GA/simulation/player/navigation/controlalgorithm/wrcontrolalgorithmbase.hh \
    src/UVF-GA/simulation/player/navigation/navigationalgorithm/uvf/uvf.hh \
    src/UVF-GA/simulation/player/navigation/navigationalgorithm/uvf/uvfobstacle.hh \
    src/UVF-GA/simulation/player/navigation/navigationalgorithm/navigationalgorithm.hh \
    src/UVF-GA/simulation/player/navigation/navigation.hh \
    src/UVF-GA/simulation/player/player.hh \
    src/UVF-GA/simulation/testcase/testcase.hh \
    src/UVF-GA/utils/entity/entity.hh \
    src/UVF-GA/utils/position/position.hh \
    src/UVF-GA/utils/timer/timer.hh \
    src/UVF-GA/utils/velocity/velocity.hh \
    src/UVF-GA/utils/utils.hh \
    src/UVF-GA/simulation/simulation.hh

# Other files
DISTFILES += LICENSE
