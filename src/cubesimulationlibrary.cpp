#include "headers/cubesimulationlibrary.h"


CubeSimulationLibrary::CubeSimulationLibrary()
{
}

CubeSimulationLibrary::~CubeSimulationLibrary()
{
  if(widget)
    delete widget;
}

void CubeSimulationLibrary::initScene(QString filename, AgentManagerFactory **facts, int amCount, AgentFactory **afacts, int aCount, QWidget *parent)
{
  widget = new CubeSimulationWidget(filename, facts, amCount, afacts, aCount, parent);
}

void CubeSimulationLibrary::showScene()
{
  if(widget)
  {
    widget->resize(640, 480);
    widget->show();
  }
}
