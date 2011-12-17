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
  AgentManager();

  AgentManager( Map *map, AgentFactory *fact, int aCount );

  ~AgentManager();

  void setType( int t );

  bool createManager( Map *m, AgentFactory *fact, int aCount );

  int getAgentsCount( void );

  QList<CubeBasic*> getAgentsList( void );

  bool getAgentCoords( int agentNum, int* coord );

  void setEnemy( QList<CubeBasic*> en );

  QList<CubeBasic*> getAgentsRoundPoint( int x, int y, int z );

  bool makeStep( void );

protected:
  virtual unsigned char makePlan( int agentNum )
  {
    return qrand() % 256;
  }

private:
  bool setStartPositions( void );
};

#endif // AGENTMANAGER_H