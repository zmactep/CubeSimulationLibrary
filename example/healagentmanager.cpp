#include "healagentmanager.h"

HealAgentManager::HealAgentManager() : AgentManager()
{
}

HealAgentManager::HealAgentManager(Map *map, AgentFactory *fact, int aCount) :
  AgentManager(map, fact,aCount)
{
}

void HealAgentManager::init()
{
  setType(AGENT_PARALLEL_TYPE);
}

unsigned char HealAgentManager::makePlan(int agentNum)
{
  int coord[3];

  qDebug() << "Heal step!";

  getAgentCoords(agentNum,coord);


  Cube *cube;
  unsigned char plan = 0;
  for( int y = coord[1]-1; y < coord[1]+2; y++ )
    for( int z = coord[2]-1; z < coord[2]+2; z++ )
      for( int x = coord[0]-1; x < coord[0]+2; x++ )
      {
        cube = subjMap->getCube(x,y,z);
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

        if(isEnemy(x,y,z))
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

    cube = subjMap->getCube(coord[0] + i, coord[1] + j, coord[2] + k);
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

  return plan;
}

void HealAgentManager::getAllMapInfo()
{
  int l, w, h;
  l = subjMap->getLevels();
  w = subjMap->getWidth();
  h = subjMap->getHeight();

  float *inputs = new float[w*h*l*5];

  QString string = "";
  int inputsIterator = 0;
  int infection = 0;
  for( int i = 0; i < l; i++ )
    for( int j = 0; j < h; j++ )
      for( int k = 0; k < w; k++ )
      {
        if(!subjMap->getCube(k,i,j))
        {
          qDebug() << "Cube error!";
          continue;
        }

        inputs[inputsIterator++] = subjMap->isTransparent(k,i,j);
        string = string + QString("%1").arg(inputs[inputsIterator-1]);
        inputs[inputsIterator++] = isEnemy(k,i,j);
        string = string + QString("%1").arg(inputs[inputsIterator-1]);

        infection = subjMap->getInfection(k,i,j);
        inputs[inputsIterator++] = (infection >> 2) & 0x1;
        string = string + QString("%1").arg(inputs[inputsIterator-1]);
        inputs[inputsIterator++] = (infection >> 1) & 0x1;
        string = string + QString("%1").arg(inputs[inputsIterator-1]);
        inputs[inputsIterator++] = (infection) & 0x1;
        string = string + QString("%1").arg(inputs[inputsIterator-1]);
      }

  delete inputs;
}

bool HealAgentManager::isEnemy(int x, int y, int z)
{
  int buf[3];
  for( int i = 0; i < enemy.size(); i++ )
  {
    subjMap->getCubeCoord(enemy[i], buf);
    if(buf[0] == x && buf[1] == y && buf[2] == z)
      return true;
  }

  return false;
}
