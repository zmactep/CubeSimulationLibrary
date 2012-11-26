#include <QtGui/QApplication>
#include <cubesimulationlibrary.h>

#include "healagentmanagerfactory.h"
#include "stupidagentmanagerfactory.h"

#include "healagentfactory.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CubeSimulationLibrary lib;
  AgentManagerFactory *fact[2];
  AgentFactory *afact[2];

  fact[0] = new HealAgentManagerFactory;
  fact[1] = new StupidAgentManagerFactory;

  afact[0] = new HealAgentFactory;
  afact[1] = new AgentFactory;

  lib.initScene("../example/map8.txt", fact, 2, afact, 2);

  qDebug() << "Scene inited!";

  // Delete factorys. No memory leaks any more!
  delete fact[1];
  delete fact[0];

  //
  delete afact[1];
  delete afact[0];

  lib.showScene();

  return a.exec();
}
