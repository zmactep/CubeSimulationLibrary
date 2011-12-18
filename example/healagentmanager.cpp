#include "healagentmanager.h"

HealAgentManager::HealAgentManager() : AgentManager()
{
}

HealAgentManager::HealAgentManager(Map *map, AgentFactory *fact, int aCount) :
  AgentManager(map, fact,aCount)
{
}

void HealAgentManager::init()
{
}

unsigned char HealAgentManager::makePlan(int agentNum)
{
  int coord[3];

  qDebug() << "Heal step!";

  getAgentCoords(agentNum,coord);
  int x, y, z;

  Cube *cube = NULL;

  while((!cube || (cube == agents[agentNum].getCube())))
  {
    x = qrand() % 3 - 1;
    z = qrand() % 3 - 1;
    y = qrand() % 3 - 1;

    if(x > 1)
      x = 1;
    if(y > 1)
      y = 1;
    if(z > 1)
      z = 1;

    cube = subjMap->getCube(coord[0] + x, coord[1] + y, coord[2] + z);

    qDebug() << "CUBE: " << cube << coord[0] + x << coord[1] + y << coord[2] + z;
  }
  qDebug() << "Transparent: " << cube->isTransparent();

  unsigned char plan = 0;
  if(z == -1)
    plan = plan | (1 << 7);
  if(z == 1)
    plan = plan | (1 << 6);

  if(x == -1)
    plan = plan | (1 << 5);
  if(x == 1)
    plan = plan | (1 << 4);

  if(y == -1)
    plan = plan | (1 << 3);
  if(y == 1)
    plan = plan | (1 << 2);

  if(!cube->isTransparent())
    plan = plan | (1);

  return plan;
}
