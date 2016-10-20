QT += core
QT -= gui

CONFIG += c++11

TARGET = UFV-GA
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    element.cpp \
    genotype.cpp \
    population.cpp \
    utils.cpp

HEADERS += \
    element.h \
    genotype.h \
    population.h \
    utils.h
