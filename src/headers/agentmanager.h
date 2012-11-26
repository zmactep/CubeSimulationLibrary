#ifndef AGENTMANAGER_H
#define AGENTMANAGER_H

#include "CubeSimulationLibrary_global.h"

#include <QtGlobal>
#include <QList>

#include "agent.h"
#include "agentfactory.h"

#include "map.h"

#define MANAGER_TYPE          0
#define AGENT_TYPE            1
#define AGENT_PARALLEL_TYPE   2

class CUBESIMULATIONLIBRARYSHARED_EXPORT AgentManager
{
protected:
  Agent *agents;
  int agentsCount;

  Map *subjMap;

  int type;

  int current_agent;

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

  void kickAgent( int value, int x, int y, int z );

protected:
  virtual void init( void )
  {
  }

  virtual unsigned char makePlan( int agentNum )
  {
    return qrand() % 256;
  }

private:
  bool setStartPositions( void );
  bool singleStep( int a_step );
};

#endif // AGENTMANAGER_H
