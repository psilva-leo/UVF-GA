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
QT += core
QT -= gui

# Optimization flags
QMAKE_CXXFLAGS  -= -O -O1
QMAKE_CXXFLAGS  += -O2 -ansi

# GEARSystem info
LIBS +=

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
    src/main.cpp

# Header files
HEADERS += \
    src/UVF-GA/geneticalgorithm/chromosome.h \
    src/UVF-GA/geneticalgorithm/genotype.h \
    src/UVF-GA/geneticalgorithm/population.h \
    src/UVF-GA/utils/utils.h

# Other files
DISTFILES +=
