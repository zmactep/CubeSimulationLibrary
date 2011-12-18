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
}

unsigned char HealAgentManager::makePlan(int agentNum)
{
  int coord[3];

  qDebug() << "Heal step!";

  getAgentCoords(agentNum,coord);
  int x, y, z;

  Cube *cube = NULL;

  //getAllMapInfo();

  while((!cube || (cube == agents[agentNum].getCube())))
  {
    x = qrand() % 3 - 1;
    z = qrand() % 3 - 1;
    y = qrand() % 3 - 1;

    if(x > 1)
      x = 1;
    if(y > 1)
      y = 1;
    if(z > 1)
      z = 1;

    cube = subjMap->getCube(coord[0] + x, coord[1] + y, coord[2] + z);

    qDebug() << "CUBE: " << cube << coord[0] + x << coord[1] + y << coord[2] + z;
  }
  qDebug() << "Transparent: " << cube->isTransparent();

  unsigned char plan = 0;
  if(z == -1)
    plan = plan | (1 << 7);
  if(z == 1)
    plan = plan | (1 << 6);

  if(x == -1)
    plan = plan | (1 << 5);
  if(x == 1)
    plan = plan | (1 << 4);

  if(y == -1)
    plan = plan | (1 << 3);
  if(y == 1)
    plan = plan | (1 << 2);

  if(!cube->isTransparent())
    plan = plan | (1);

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
          qDebug() << "SHIT!";
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
  for( int i = 0; i < enemy.length(); i++ )
  {
    subjMap->getCubeCoord(enemy[i], buf);
    if(buf[0] == x && buf[1] == y && buf[2] == z)
      return true;
  }

  return false;
}
