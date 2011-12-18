#ifndef HEALAGENTMANAGERFACTORY_H
#define HEALAGENTMANAGERFACTORY_H

#include <agentmanagerfactory.h>

#include "healagentmanager.h"

class HealAgentManagerFactory : public AgentManagerFactory
{
public:
  AgentManager* createManagers( int number, int param = 0 )
  {
    return new HealAgentManager[number];
  }
};

#endif // HEALAGENTMANAGERFACTORY_H
