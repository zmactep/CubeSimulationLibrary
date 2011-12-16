#ifndef CUBESIMULATIONLIBRARY_H
#define CUBESIMULATIONLIBRARY_H

#include <QtGui>

#include "CubeSimulationLibrary_global.h"
#include "cubesimulationwidget.h"

class CUBESIMULATIONLIBRARYSHARED_EXPORT CubeSimulationLibrary {
private:
  CubeSimulationWidget *widget;
public:
  CubeSimulationLibrary();
  ~CubeSimulationLibrary();

  void initScene( QString filename, AgentManagerFactory *facts = NULL, int amCount = 0,
                                    AgentFactory *afacts = NULL, int aCount = 0,
                                    QWidget *parent = 0 );

  void showScene( void );
};

#endif // CUBESIMULATIONLIBRARY_H
