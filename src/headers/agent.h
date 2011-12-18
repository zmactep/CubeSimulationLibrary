#ifndef AGENT_H
#define AGENT_H

#define MAX_HEALTH 100
#define AGENT_KICK 20

#include "CubeSimulationLibrary_global.h"

#include <stdio.h>

#include <QDebug>
#include <QList>

#include "cubebasic.h"
#include "map.h"

#define DIRECTION_NORD(x)  (bool)(0x80 & x)
#define DIRECTION_SOUTH(x) (bool)(0x40 & x)
#define DIRECTION_WEST(x)  (bool)(0x20 & x)
#define DIRECTION_EAST(x)  (bool)(0x10 & x)
#define DIRECTION_UP(x)    (bool)(0x08 & x)
#define DIRECTION_DOWN(x)  (bool)(0x04 & x)

#define ACTION_MASK(x)     (bool)(0x03 & x)

#define ACTION_KILL(x)     (bool)(0x02 & x) && (bool)(0x01 & x)
#define ACTION_INFECT(x)   (bool)(0x02 & x) && (bool)!(0x01 & x)
#define ACTION_HEAL(x)     (bool)!(0x02 & x) && (bool)(0x01 & x)
#define ACTION_GO(x)       (bool)!(0x02 & x) && (bool)!(0x01 & x)

//! Agent class.
/*!
  Agent is the citizen of the Environment. Depense on the team, it can be
  an infector or a healer.
*/
class CUBESIMULATIONLIBRARYSHARED_EXPORT Agent
{
protected:
  //! Agent`s heals.
  /*!
    When the agent health is 0, it decativates.
  */
  int health;

  //! Agent`s plan.
  /*!
    Encoded Agent`s plan for the nex iteration.
  */
  unsigned char agentPlan;

  //! Agent`s CubeBasic.
  /*!
    A CubeBasic whitch the Agent is in.
  */
  CubeBasic *myCube;

public:
  //! Constructor.
  /*!
    Constructs full health Agent.
  */
  Agent()
  {
    health = MAX_HEALTH;
    agentPlan = 0;
  }

  //! Set plan method.
  /*!
    Sets the Agent`s plan for the next iteration.
    \param nPlan an encoded plan
  */
  inline void setPlan( unsigned char nPlan )
  {
    agentPlan = nPlan;
  }

  //! Get plan method.
  /*!
    Gets the Agent`s plan for the next iteration.
    \return an encoded plan
  */
  inline unsigned char getPlan( void )
  {
    return agentPlan;
  }

  //! Make plan method.
  /*!
    Make Agent`s plan for the next iteration.
    \param map pointer to Map where Agent lives
    \param enemy cubes with enemy
    \return an encoded plan
  */
  virtual unsigned char makePlan( Map* map, QList<CubeBasic*> enemy )
  {
    agentPlan = 0;
    return agentPlan;
  }

  //! Get health method.
  /*!
    Gets the Agent`s health.
    \return the health of the Agent
  */
  inline int getHealth( void )
  {
    return health;
  }

  //! Increment health method.
  /*!
    Increments Agent`s health for given value.
    \param value an incremention value
    \return the new health of the Agent
  */
  inline int incHealth( int value )
  {
    health += value;
    if(health > MAX_HEALTH)
      health = MAX_HEALTH;

    return health;
  }

  //! Decrement health method.
  /*!
    Decrements Agent`s health for given value.
    \param value a Decremention value
    \return the new health of the Agent
  */
  inline int decHealth( int value )
  {
    health -= value;
    if(health < 0)
      health = 0;

    return health;
  }

  //! Set Cube method.
  /*!
    \param cube new CubeBasic of Agent
    \return the CubeBasic, that was set
  */
  inline CubeBasic* setCube( CubeBasic *cube )
  {
    myCube = cube;

    return myCube;
  }

  //! Get Cube method.
  /*!
    Gets the Agent`s CubeBasic.
    \return the Agent`s CubeBasic
  */
  inline CubeBasic* getCube( void )
  {
    return myCube;
  }

  //! Make Agent step method.
  /*!
    \return the result of operation
  */
  inline bool makeStep( Map* map )
  {
    return makeStepPrivate(map);
  }


private:
  bool makeStepPrivate( Map *map );
};

#endif // AGENT_H
