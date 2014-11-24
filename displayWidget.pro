TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += core gui opengl


SOURCES += main.cpp \
    displaygl.cpp \
    mwindow.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    displaygl.h \
    mwindow.h

OTHER_FILES += \
    items.txt

