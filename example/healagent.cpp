#include "healagent.h"

HealAgent::HealAgent()
{
}

unsigned char HealAgent::makePlan(Map *map, QList<CubeBasic *> enemy, int coord[])
{
  qDebug() << "Heal step!";

  Cube *cube;
  unsigned char plan = 0;
  for( int y = coord[1]-1; y < coord[1]+2; y++ )
    for( int z = coord[2]-1; z < coord[2]+2; z++ )
      for( int x = coord[0]-1; x < coord[0]+2; x++ )
      {
        cube = map->getCube(x,y,z);
        if(!cube)
          continue;

        if(x == coord[0] && y == coord[1] && z == coord[2])
          continue;

        if(x > coord[0])
          plan = plan | (1 << 4);
        else if(x < coord[0])
          plan = plan | (1 << 5);

        if(y > coord[1])
          plan = plan | (1 << 2);
        else if(y < coord[1])
          plan = plan | (1 << 3);

        if(z > coord[2])
          plan = plan | (1 << 6);
        else if(z < coord[2])
          plan = plan | (1 << 7);

        if(isEnemy(map, enemy, x,y,z))
        {
          plan = plan | 3;

          return plan;
        }

        if(cube->getInfection())
        {
          plan = plan | 1;

          return plan;
        }

        plan = 0;
      }


  int i, j, k;
  cube = NULL;
  while(!cube)
  {
    i = qrand() % 3 - 1;
    j = qrand() % 3 - 1;
    k = qrand() % 3 - 1;

    if(i > 1)
      i = 1;
    if(j > 1)
      j = 1;
    if(k > 1)
      k = 1;

    if(!i && !j && !k)
      continue;

    cube = map->getCube(coord[0] + i, coord[1] + j, coord[2] + k);
    qDebug() << "CUBE: " << cube << coord[0] + i << coord[1] + j << coord[2] + k;
    if(!cube)
      continue;

    if(!cube->isTransparent())
      cube = NULL;
  }

  plan = 0;
  if(k == -1)
    plan = plan | (1 << 7);
  if(k == 1)
    plan = plan | (1 << 6);

  if(i == -1)
    plan = plan | (1 << 5);
  if(i == 1)
    plan = plan | (1 << 4);

  if(j == -1)
    plan = plan | (1 << 3);
  if(j == 1)
    plan = plan | (1 << 2);

  setPlan(plan);

  return plan;
}

bool HealAgent::isEnemy(Map *map, QList<CubeBasic *> enemy, int x, int y, int z)
{
  int buf[3];
  for( int i = 0; i < enemy.size(); i++ )
  {
    map->getCubeCoord(enemy[i], buf);
    if(buf[0] == x && buf[1] == y && buf[2] == z)
      return true;
  }

  return false;
}
