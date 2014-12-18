TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += core gui opengl network

macx {
    LIBS +=-L"/System/Library/Frameworks"
    LIBS +=-L"/System/Library/Frameworks/OpenGL.framework/Libraries"
    LIBS += -framework GLUT -framework OpenGL -framework Cocoa
}

TARGET = MazeOfAlignment

SOURCES += main.cpp \
    displaygl.cpp \
    mwindow.cpp \
    weights.cpp \
    items.cpp \
    adjacency.cpp \
    room.cpp \
    roomlist.cpp \
    allItems.cpp \
    networkofalignment.cpp \
    question.cpp \
    player.cpp \
    serverinfo.cpp \
    monster.cpp \
    zombie.cpp


HEADERS += \
    displaygl.h \
    mwindow.h \
    adjacency.h \
    weights.h \
    items.h \
    room.h \
    allItems.h \
    roomlist.h \
    networkofalignment.h \
    question.h \
    player.h \
    serverinfo.h \
    monster.h \
    bst.h \
    node.h \
    zombie.h

OTHER_FILES += \
    items.txt

