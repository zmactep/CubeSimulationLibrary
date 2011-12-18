#include "headers/agentmanager.h"

AgentManager::AgentManager()
{
  agents = NULL;
  agentsCount = 0;

  subjMap = NULL;

  type = 0;
}

AgentManager::AgentManager(Map *map, AgentFactory *fact, int aCount)
{
  createManager(map, fact, aCount);
}

AgentManager::~AgentManager()
{
  if(subjMap)
    delete subjMap;
  subjMap = NULL;

  if(agents)
    delete[] agents;
  agents = NULL;
}

void AgentManager::setType(int t)
{
  type = t;
}

bool AgentManager::createManager(Map *m, AgentFactory *fact, int aCount)
{
  subjMap = new Map();
  if(!subjMap)
    return false;

  agents = fact->createAgents(aCount);
  if(!agents)
    return false;
  agentsCount = aCount;

  type = 0;

  map = m;

  subjMap->copyOf(map);

  return setStartPositions();
}

int AgentManager::getAgentsCount()
{
  return agentsCount;
}

QList<CubeBasic *> AgentManager::getAgentsList()
{
  QList<CubeBasic*> list;

  for( int i = 0; i < agentsCount; i++ )
    list.append(agents[i].getCube());

  return list;
}

bool AgentManager::getAgentCoords(int agentNum, int *coord)
{
  return map->getCubeCoord(agents[agentNum].getCube(), coord);
}

void AgentManager::setEnemy(QList<CubeBasic *> en)
{
  enemy = en;
  for( int i = 0; i < enemy.length(); i++ )
    enemy.replace(i, subjMap->getSameCubeFrom(map, enemy.at(i)));
}

QList<CubeBasic*> AgentManager::getAgentsRoundPoint( int x, int y, int z )
{
  int coord[3];
  QList<CubeBasic*> list;

  for( int i = 0; i < agentsCount; i++ )
  {
    map->getCubeCoord(agents[i].getCube(), coord);
    if( coord[0] >= x - MAX_VIEW_RADIUS && coord[0] <= x + MAX_VIEW_RADIUS &&
        coord[1] >= y - MAX_VIEW_RADIUS && coord[1] <= y + MAX_VIEW_RADIUS &&
        coord[2] >= z - MAX_VIEW_RADIUS && coord[2] <= z + MAX_VIEW_RADIUS )
      if(!list.contains(agents[i].getCube()))
        list.append(agents[i].getCube());
  }

  return list;
}

bool AgentManager::makeStep( void )
{
  static int a_step = 0;
  int a_coord[3];
  bool flag = true;

  if(!map->getCubeCoord(agents[a_step].getCube(), a_coord))
    flag = false;
  else
  {
    ///////////////////////////////////////////////////////////
    Map* tmpMap = map->getSubMap(a_coord[0], a_coord[1],
                                 a_coord[2], MAX_VIEW_RADIUS);
    subjMap->appendSubMap(tmpMap, a_coord[0], a_coord[1],
                                  a_coord[2], MAX_VIEW_RADIUS);
    if(tmpMap)
    {
      delete tmpMap;
      tmpMap = NULL;
    }

    ///////////////////////////////////////////////////////////
    if(type == MANAGER_TYPE)
      agents[a_step].setPlan(makePlan(a_step));
    else
      agents[a_step].makePlan(subjMap, enemy);

    agents[a_step].makeStep(map);

    ///////////////////////////////////////////////////////////
    tmpMap = map->getSubMap(a_coord[0], a_coord[1],
                            a_coord[2], MAX_VIEW_RADIUS);
    subjMap->appendSubMap(tmpMap, a_coord[0], a_coord[1],
                                  a_coord[2], MAX_VIEW_RADIUS);
    if(!tmpMap)
    {
      delete tmpMap;
      tmpMap = NULL;
    }
  }

  a_step++;
  if(a_step > agentsCount)
    a_step = 0;

  return flag;
}

bool AgentManager::setStartPositions( void )
{
  if(subjMap->getTransparentCubesCount() < agentsCount)
    return false;

  int count = agentsCount;
  int x, y, z;

  while(count > 0)
  {
    x = qrand() % subjMap->getWidth();
    y = qrand() % subjMap->getLevels();
    z = qrand() % subjMap->getHeight();

    if(subjMap->isTransparent(x,y,z))
    {
      CubeBasic *cube = map->getCube(x,y,z);

      agents[agentsCount-count].setCube(cube);
      count--;
    }
  }

  return true;
}
