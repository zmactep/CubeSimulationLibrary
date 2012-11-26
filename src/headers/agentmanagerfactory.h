#ifndef AGENTMANAGERFACTORY_H
#define AGENTMANAGERFACTORY_H

#include "CubeSimulationLibrary_global.h"

#include "agentmanager.h"

class CUBESIMULATIONLIBRARYSHARED_EXPORT AgentManagerFactory
{
public:
  virtual AgentManager* createManagers( int number, int param = 0 )
  {
    return new AgentManager[number];
  }
};

#endif // AGENTMANAGERFACTORY_H
