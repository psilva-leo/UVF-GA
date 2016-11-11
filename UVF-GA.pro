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
    src/UVF-GA/geneticalgorithm/chromosome.cpp \
    src/UVF-GA/geneticalgorithm/genotype.cpp \
    src/UVF-GA/geneticalgorithm/population.cpp \
    src/UVF-GA/utils/utils.cpp \
    src/main.cpp \
    src/3rdparty/sslworld/physics/pball.cpp \
    src/3rdparty/sslworld/physics/pbox.cpp \
    src/3rdparty/sslworld/physics/pcylinder.cpp \
    src/3rdparty/sslworld/physics/pfixedbox.cpp \
    src/3rdparty/sslworld/physics/pground.cpp \
    src/3rdparty/sslworld/physics/pobject.cpp \
    src/3rdparty/sslworld/physics/pray.cpp \
    src/3rdparty/sslworld/physics/pworld.cpp \
    src/3rdparty/sslworld/robot.cpp \
    src/3rdparty/sslworld/sslworld.cpp \
    src/3rdparty/sslworld/fieldconfig.cpp \
    src/UVF-GA/simulation/entity/player/navigation/controlalgorithm/pid/pid.cc \
    src/UVF-GA/simulation/entity/player/navigation/controlalgorithm/controlalgorithm.cc \
    src/UVF-GA/simulation/entity/player/navigation/controlalgorithm/controlalgorithmparameters.cc \
    src/UVF-GA/simulation/entity/player/navigation/navigationalgorithm/uvf/uvf.cc \
    src/UVF-GA/simulation/entity/player/navigation/navigationalgorithm/uvf/uvfobstacle.cc \
    src/UVF-GA/simulation/entity/player/navigation/navigationalgorithm/navigationalgorithm.cc \
    src/UVF-GA/simulation/entity/player/navigation/navigation.cc \
    src/UVF-GA/simulation/entity/player/player.cpp \
    src/UVF-GA/simulation/entity/entity.cc \
    src/UVF-GA/utils/position.cpp \
    src/UVF-GA/utils/timer.cc \
    src/UVF-GA/utils/velocity.cpp \
    src/3rdparty/soccerview/util/field.cc \
    src/3rdparty/soccerview/gltext.cc \
    src/3rdparty/soccerview/soccerview.cc

# Header files
HEADERS += \
    src/UVF-GA/geneticalgorithm/chromosome.h \
    src/UVF-GA/geneticalgorithm/genotype.h \
    src/UVF-GA/geneticalgorithm/population.h \
    src/UVF-GA/utils/utils.h \
    src/3rdparty/sslworld/physics/pball.h \
    src/3rdparty/sslworld/physics/pbox.h \
    src/3rdparty/sslworld/physics/pcylinder.h \
    src/3rdparty/sslworld/physics/pfixedbox.h \
    src/3rdparty/sslworld/physics/pground.h \
    src/3rdparty/sslworld/physics/pobject.h \
    src/3rdparty/sslworld/physics/pray.h \
    src/3rdparty/sslworld/physics/pworld.h \
    src/3rdparty/sslworld/robot.h \
    src/3rdparty/sslworld/sslworld.h \
    src/3rdparty/sslworld/fieldconfig.h \
    src/UVF-GA/simulation/entity/player/navigation/controlalgorithm/pid/pid.hh \
    src/UVF-GA/simulation/entity/player/navigation/controlalgorithm/controlalgorithm.hh \
    src/UVF-GA/simulation/entity/player/navigation/controlalgorithm/controlalgorithmparameters.hh \
    src/UVF-GA/simulation/entity/player/navigation/controlalgorithm/wrcontrolalgorithmbase.hh \
    src/UVF-GA/simulation/entity/player/navigation/navigationalgorithm/uvf/uvf.hh \
    src/UVF-GA/simulation/entity/player/navigation/navigationalgorithm/uvf/uvfobstacle.hh \
    src/UVF-GA/simulation/entity/player/navigation/navigationalgorithm/navigationalgorithm.hh \
    src/UVF-GA/simulation/entity/player/navigation/navigation.hh \
    src/UVF-GA/simulation/entity/player/player.h \
    src/UVF-GA/simulation/entity/entity.hh \
    src/UVF-GA/utils/position.h \
    src/UVF-GA/utils/timer.hh \
    src/UVF-GA/utils/velocity.h \
    src/3rdparty/soccerview/util/field.hh \
    src/3rdparty/soccerview/util/field_default_constants.hh \
    src/3rdparty/soccerview/util/geometry.hh \
    src/3rdparty/soccerview/util/gvector.hh \
    src/3rdparty/soccerview/util/timer.hh \
    src/3rdparty/soccerview/util/util.h \
    src/3rdparty/soccerview/gltext.hh \
    src/3rdparty/soccerview/soccerview.hh

# Other files
DISTFILES += LICENSE
