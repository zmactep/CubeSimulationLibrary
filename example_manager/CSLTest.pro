#-------------------------------------------------
#
# Project created by QtCreator 2011-12-17T02:22:56
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = CSLTest
TEMPLATE = app
CONFIG += build_all console

SOURCES += main.cpp \
    stupidagentmanager.cpp \
	healagentmanager.cpp

HEADERS  += \
    stupidagentmanager.h \
    stupidagentmanagerfactory.h \
	healagentmanager.h \
    healagentmanagerfactory.h

INCLUDEPATH += src/headers

debug {
  LIBS += -L "debug" \
          -l CubeSimulationLibrary
}

release {
  LIBS += -L "release" \
          -l CubeSimulationLibrary
}
