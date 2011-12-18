#ifndef HEALAGENTMANAGER_H
#define HEALAGENTMANAGER_H

#include <agentmanager.h>

class HealAgentManager : public AgentManager
{
public:
  HealAgentManager();
  HealAgentManager( Map *map, AgentFactory *fact, int aCount );

protected:
  void init( void );
  unsigned char makePlan( int agentNum );
};

#endif // HEALAGENTMANAGER_H
