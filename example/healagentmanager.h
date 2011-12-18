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

private:
  void getAllMapInfo( void );
  bool isEnemy (int x, int y, int z);
};

#endif // HEALAGENTMANAGER_H
