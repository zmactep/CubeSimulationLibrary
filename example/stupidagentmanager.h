#ifndef STUPIDAGENTMANAGER_H
#define STUPIDAGENTMANAGER_H

#include <agentmanager.h>

class StupidAgentManager : public AgentManager
{
public:
  StupidAgentManager();
  StupidAgentManager( Map *map, AgentFactory *fact, int aCount );

protected:
  unsigned char makePlan( int agentNum );
};

#endif // STUPIDAGENTMANAGER_H
