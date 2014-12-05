TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += core gui opengl

SOURCES += main.cpp \
    displaygl.cpp \
    mwindow.cpp \
    weights.cpp \
    items.cpp \
    stats.cpp \
    adjacency.cpp \
    room.cpp \
    roomlist.cpp \
    allItems.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    displaygl.h \
    mwindow.h \
    adjacency.h \
    weights.h \
    stats.h \
    items.h \
    room.h \
    allItems.h \
    roomlist.h

OTHER_FILES += \
    items.txt
