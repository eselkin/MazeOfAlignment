TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += network

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

