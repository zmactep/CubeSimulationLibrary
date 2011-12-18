#include <QtGui/QApplication>
#include <cubesimulationlibrary.h>

#include "healagentmanagerfactory.h"
#include "stupidagentmanagerfactory.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CubeSimulationLibrary lib;
  AgentManagerFactory *fact[2];
  fact[0] = new HealAgentManagerFactory;
  fact[1] = new StupidAgentManagerFactory;

  lib.initScene("../example/map5.txt", fact, 2);

  // Delete factorys. No memory leaks any more!
  delete fact[1];
  delete fact[0];

  lib.showScene();

  return a.exec();
}
