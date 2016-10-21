QT += core
QT -= gui

CONFIG += c++11

TARGET = UFV-GA
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    genotype.cpp \
    population.cpp \
    utils.cpp \
    chromosome.cpp

HEADERS += \
    genotype.h \
    population.h \
    utils.h \
    chromosome.h
