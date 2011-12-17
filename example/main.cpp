#include <QtGui>
#include <cubesimulationlibrary.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CubeSimulationLibrary lib;

  AgentManagerFactory fact[2];
  lib.initScene("../example/map5.txt", fact, 2);
  lib.showScene();
  
  return a.exec();
}
