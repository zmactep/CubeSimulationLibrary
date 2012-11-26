#ifndef HEALAGENTFACTORY_H
#define HEALAGENTFACTORY_H

#include <agentfactory.h>
#include "healagent.h"

class HealAgentFactory : public AgentFactory
{
public:
  Agent* createAgents( int number, int param = 0 )
  {
    return new HealAgent[number];
  }
};

#endif // HEALAGENTFACTORY_H
