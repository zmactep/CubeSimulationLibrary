#ifndef STUPIDAGENTMANAGERFABRIC_H
#define STUPIDAGENTMANAGERFABRIC_H

#include <agentmanagerfactory.h>

#include "stupidagentmanager.h"

class StupidAgentManagerFactory : public AgentManagerFactory
{
public:
  AgentManager* createManagers( int number, int param = 0 )
  {
    return new StupidAgentManager[number];
  }
};

#endif // STUPIDAGENTMANAGERFABRIC_H
