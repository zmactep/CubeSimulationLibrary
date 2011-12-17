#-------------------------------------------------
#
# Project created by QtCreator 2011-12-17T02:22:56
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = CSLTest
TEMPLATE = app
CONFIG += build_all

SOURCES += main.cpp

HEADERS  +=

INCLUDEPATH += src/headers

debug {
  LIBS += -L "debug" \
          -l CubeSimulationLibrary
}

release {
  LIBS += -L "release" \
          -l CubeSimulationLibrary
}
