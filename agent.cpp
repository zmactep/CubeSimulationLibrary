#include "agent.h"

bool Agent::makeStepPrivate( Map *map )
{
  int coord[3];
  CubeBasic *cube;
  //
  //  w-1  w+1
  //    w n e   h-1
  //      s     h+1
  //  u l-1
  //  d l+1

  map->getCubeCoord(myCube, coord);

  qDebug() << "From [" << coord[0] << ", " << coord[1] << ", " << coord[2] << "]";

  if(DIRECTION_WEST(agentPlan))
    coord[0] -= 1;
  if(DIRECTION_EAST(agentPlan))
    coord[0] += 1;

  if(DIRECTION_UP(agentPlan))
    coord[1] -= 1;
  if(DIRECTION_DOWN(agentPlan))
    coord[1] += 1;

  if(DIRECTION_NORD(agentPlan))
    coord[2] -= 1;
  if(DIRECTION_SOUTH(agentPlan))
    coord[2] += 1;

  cube = map->getCube(coord[0], coord[1], coord[2]);

  qDebug() << "To [" << coord[0] << ", " << coord[1] << ", " << coord[2] << "]";

  if(ACTION_KILL(agentPlan))
  {
    qDebug() << "Action KILL";
    if(cube == NULL || !cube->isTransparent())
      return false;
    qDebug() << "OK!";
  }
  else if(ACTION_GO(agentPlan))
  {
    qDebug() << "Action GO";
    if(cube == NULL || !cube->isTransparent())
      return false;

    myCube = cube;
    qDebug() << "OK!";
  }
  else if(ACTION_HEAL(agentPlan))
  {
    qDebug() << "Action HEAL";
    if(cube == NULL || cube->isTransparent())
      return false;

    cube->decInfection();
    qDebug() << "OK!";
  }
  else if(ACTION_INFECT(agentPlan))
  {
    qDebug() << "Action INFECT";
    if(cube == NULL || cube->isTransparent())
      return false;

    cube->incInfection();
    qDebug() << "OK!";
  }

  return true;
}
