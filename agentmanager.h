#ifndef AGENTMANAGER_H
#define AGENTMANAGER_H

#include "CubeSimulationLibrary_global.h"

#include <QtGlobal>
#include <QList>

#include "agent.h"
#include "agentfactory.h"

#include "map.h"

#define MANAGER_TYPE 0
#define AGENT_TYPE   1

class CUBESIMULATIONLIBRARYSHARED_EXPORT AgentManager
{
protected:
  Agent *agents;
  int agentsCount;

  Map *subjMap;

  int type;

  QList<CubeBasic*> enemy;

private:
  Map *map;

public:
  AgentManager()
  {
    agents = NULL;
    agentsCount = 0;

    subjMap = NULL;

    type = 0;
  }

  AgentManager( Map *map, AgentFactory *fact, int aCount )
  {
    createManager(map, fact, aCount);
  }

  ~AgentManager()
  {
    if(subjMap)
      delete subjMap;
    subjMap = NULL;

    if(agents)
      delete[] agents;
    agents = NULL;
  }

  inline void setType( int t )
  {
    type = t;
  }

  inline bool createManager( Map *m, AgentFactory *fact, int aCount )
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

  inline int getAgentsCount( void )
  {
    return agentsCount;
  }

  inline QList<CubeBasic*> getAgentsList( void )
  {
    QList<CubeBasic*> list;

    for( int i = 0; i < agentsCount; i++ )
      list.append(agents[i].getCube());

    return list;
  }

  inline bool getAgentCoords( int agentNum, int* coord )
  {
    return map->getCubeCoord(agents[agentNum].getCube(), coord);
  }

  inline void setEnemy( QList<CubeBasic*> en )
  {
    enemy = en;
    for( int i = 0; i < enemy.length(); i++ )
      enemy.replace(i, subjMap->getSameCubeFrom(map, enemy.at(i)));
  }

  QList<CubeBasic*> getAgentsRoundPoint( int x, int y, int z );

  bool makeStep( void );

protected:
  virtual unsigned char makePlan( int agentNum )
  {
    //return 0;
    return qrand() % 256;
  }

private:
  bool setStartPositions( void );
};

#endif // AGENTMANAGER_H
