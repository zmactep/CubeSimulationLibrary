#ifndef AGENTFACTORY_H
#define AGENTFACTORY_H

#include "CubeSimulationLibrary_global.h"

#include "agent.h"

class CUBESIMULATIONLIBRARYSHARED_EXPORT AgentFactory
{
public:
  virtual Agent* createAgents( int number, int param = 0 )
  {
    return new Agent[number];
  }
};

#endif // AGENTFACTORY_H
