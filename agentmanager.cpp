#include "agentmanager.h"

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
    qDebug() << "BSGM";
    Map* tmpMap = map->getSubMap(a_coord[0], a_coord[1],
                                 a_coord[2], MAX_VIEW_RADIUS);
    qDebug() << "BSAM";
    subjMap->appendSubMap(tmpMap, a_coord[0], a_coord[1],
                                  a_coord[2], MAX_VIEW_RADIUS);
    qDebug() << "BSD";
    delete tmpMap;

    ///////////////////////////////////////////////////////////
    qDebug() << "STEP";
    if(type == MANAGER_TYPE)
      agents[a_step].setPlan(makePlan(a_step));
    else
      agents[a_step].makePlan(subjMap, enemy);

    agents[a_step].makeStep(map);

    ///////////////////////////////////////////////////////////
    qDebug() << "ASGM";
    tmpMap = map->getSubMap(a_coord[0], a_coord[1],
                            a_coord[2], MAX_VIEW_RADIUS);
    qDebug() << "ASAM";
    subjMap->appendSubMap(tmpMap, a_coord[0], a_coord[1],
                                  a_coord[2], MAX_VIEW_RADIUS);
    qDebug() << "ASD";
    delete tmpMap;
  }

  a_step++;
  if(a_step >= agentsCount)
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
