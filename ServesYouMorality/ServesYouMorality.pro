#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T23:07:05
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = ServesYouMorality
CONFIG   += console

CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    moralityserver.cpp \
    threadofmorality.cpp \
    moralthread.cpp

HEADERS += \
    moralityserver.h \
    threadofmorality.h \
    moralthread.h
