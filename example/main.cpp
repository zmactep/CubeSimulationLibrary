#include <QtGui>
#include <cubesimulationlibrary.h>

#include "stupidagentmanagerfactory.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CubeSimulationLibrary lib;

  AgentManagerFactory *fact[2];
  fact[0] = new AgentManagerFactory;
  fact[1] = new StupidAgentManagerFactory;

  lib.initScene("../example/map5.txt", fact, 2);
  lib.showScene();
  
  return a.exec();
}
