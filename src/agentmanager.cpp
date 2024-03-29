#include "headers/agentmanager.h"

AgentManager::AgentManager()
{
  agents = NULL;
  agentsCount = 0;

  subjMap = NULL;

  current_agent = 0;

  type = 0;
}

AgentManager::AgentManager(Map *map, AgentFactory *fact, int aCount)
{
  createManager(map, fact, aCount);
}

AgentManager::~AgentManager()
{
  qDebug() << "Delete AgentManager";

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

  current_agent = 0;

  init();

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
    if(agents[i].getHealth())
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
        if(agents[i].getHealth())
          list.append(agents[i].getCube());
  }

  return list;
}

bool AgentManager::makeStep( void )
{
  bool flag = true;

  qDebug() << "Agent's" << current_agent << "step!";

  if(type == AGENT_PARALLEL_TYPE)
  {
    for( int i = 0; i < agentsCount; i++ ) {
      flag = flag && singleStep(i);
    }

    return flag;
  }


  singleStep(current_agent);

  current_agent++;
  if(current_agent > agentsCount)
    current_agent = 0;

  return flag;
}

void AgentManager::kickAgent(int value, int x, int y, int z )
{
  for( int i = 0; i < agentsCount; i++ )
  {
    int coord[3];
    map->getCubeCoord(agents[i].getCube(), coord);
    if(x == coord[0] && y  == coord[1] && z == coord[2])
      agents[i].decHealth(value);
  }
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

bool AgentManager::singleStep( int a_step )
{
  int a_coord[3];
  bool flag = true;

  if(!map->getCubeCoord(agents[a_step].getCube(), a_coord) || !agents[a_step].getHealth())
    flag = false;
  else
  {
    ///////////////////////////////////////////////////////////
    Map* tmpMap = map->getSubMap(a_coord[0], a_coord[1],
                                 a_coord[2], MAX_VIEW_RADIUS);
    subjMap->appendSubMap(tmpMap, a_coord[0], a_coord[1],
                                  a_coord[2], MAX_VIEW_RADIUS);

    ///////////////////////////////////////////////////////////
    if(type == MANAGER_TYPE)
      agents[a_step].setPlan(makePlan(a_step));
    else
      agents[a_step].setPlan(agents[a_step].makePlan(subjMap, enemy, a_coord));

    agents[a_step].makeStep(map);

    if(tmpMap)
    {
      delete tmpMap;
      tmpMap = NULL;
    }

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

  return flag;
}
