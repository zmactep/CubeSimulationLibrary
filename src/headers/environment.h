#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "CubeSimulationLibrary_global.h"

#include <QDebug>
#include <QThread>
#include <QTimer>

#include <QList>
#include <QMap>

#include "map.h"

#include "agentmanager.h"
#include "agentmanagerfactory.h"

// Params for agent`s simulationj
#define VIEW_RADIUS     3
#define ONE_HIT_FORCE   20
#define STEPS_PER_SECOND 10

//!  Environment class.
/*!
  The main Simulation class. It has the real Map and agents managers.
  Gives the agent managers API for actions in the Map.
*/
class CUBESIMULATIONLIBRARYSHARED_EXPORT Environment : public QThread
{
  Q_OBJECT
private:
  //! Real map.
  /*!
    The real map, that has the information of all cubes state.
  */
  Map *realMap;

  //! Live flag.
  /*!
    If this flag is true, the simulation is working, else paused.
  */
  bool startFlag;

  //! Teams.
  /*!
    AgentManagers that play our game
  */
  AgentManager** teams;

  //! Teams count.
  /*!
    Number of AgentManagers.
  */
  int teamCount;

public:
  //!  Map setup constructor.
  /*!
    Creates Environment with given Map. Creates two teams.
    \param map a Map that will be used by Environment
    \param facts array of factories to create teams
    \param amCount number of teams
    \param afacts factories to create Agents in the teams
    \param aCount number of Agents per Team
    \sa Environment(), setMap() and changeMap()
  */
  Environment( Map* map = NULL, AgentManagerFactory **facts = NULL, int amCount = 0,
                                AgentFactory **afacts = NULL, int aCount = 0 );

  //!  Destructor.
  /*!
    Deletes all used memory when the object`s live ends.
    \sa deleteMap()
  */
  ~Environment();

  //!  Map setup method.
  /*!
    Sets Environment Map as given.
    \param map a Map that will be used by Environment
    \return pointer to the new Map
    \sa Environment(), Environment(Map *map) and changeMap()
  */
  Map* setMap( Map* map );

  //! Get Map method.
  /*!
    Get Environment`s Map.
    \return pointer to theMap
    \sa Environment(), Environment(Map *map) and changeMap()
  */
  Map* getMap( void );

  //!  Map change method.
  /*!
    Change Environment Map as given and returns old map.
    \param map a Map that will be used by Environment
    \return pointer to the old Map
    \sa Environment(), Environment(Map *map) and setMap()
  */
  Map* changeMap( Map* map );

  //! Get start flag method.
  /*!
    \return true, if simulation started or false if not
  */
  bool isStarted( void );

  //! Simlation step method.
  /*!
    One step of simulation.
  */
  void simulationStep( void );

  //! Export agents method.
  /*!
    \param teamNum the number of team to get Agents from
    \return list of all Agents
  */
  QList<Point3D> exportAgents( int teamNum );

  //! Run method.
  /*!
    New thread working method.
  */
  void run( void );

signals:
  //! State changed signal.
  /*!
    This signal is sent, when something had happend in the Environment.
  */
  void stateChanged( void );

public slots:
  //! Force state change slot.
  /*!
    Force emits state change signal.
  */
  void slot_setStateChanged( void );

  //! Toggle Start Flag slot.
  /*!
    Toggles start flag, so the simulation may be paused or resumed.
  */
  void slot_toggleStart( void );

  //! Make next step slot.
  /*!
    One more simulation iteration.
  */
  void slot_nextStep( void );

private:
  //!  Delete current Map method.
  /*!
    Deletes used Map.
    \sa ~Environment()
  */
  void deleteMap( void );

  //! Get enemy agents method.
  /*!
    \param teamNumber number of current team
    \return list of enemys around current team
  */
  QList<CubeBasic*> getEnemyAgents( int teamNumber );
};

#endif // ENVIRONMENT_H
