#include "stupidagentmanager.h"

StupidAgentManager::StupidAgentManager() : AgentManager()
{
}

StupidAgentManager::StupidAgentManager(Map *map, AgentFactory *fact, int aCount) :
  AgentManager(map, fact, aCount)
{
}

unsigned char StupidAgentManager::makePlan(int agentNum)
{
  return 0;
}
