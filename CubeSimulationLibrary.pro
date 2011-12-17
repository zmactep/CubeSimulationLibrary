#-------------------------------------------------
#
# Project created by QtCreator 2011-12-16T23:20:48
#
#-------------------------------------------------

QT       += opengl

TARGET = CubeSimulationLibrary
TEMPLATE = lib

CONFIG += build_all

DEFINES += CUBESIMULATIONLIBRARY_LIBRARY

SOURCES += cubesimulationlibrary.cpp \
    map.cpp \
    environment.cpp \
    cubesimulationwidget.cpp \
    cubesimulationview.cpp \
    agentmanager.cpp \
    agent.cpp

HEADERS += cubesimulationlibrary.h\
        CubeSimulationLibrary_global.h \
    map.h \
    environment.h \
    cubesimulationwidget.h \
    cubesimulationview.h \
    cubebasic.h \
    cube.h \
    agentmanagerfactory.h \
    agentmanager.h \
    agentfactory.h \
    agent.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE1F3C352
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = CubeSimulationLibrary.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
