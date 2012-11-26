#ifndef HEALAGENT_H
#define HEALAGENT_H

#include <agent.h>

class HealAgent : public Agent
{
public:
  HealAgent();

  unsigned char makePlan( Map* map, QList<CubeBasic*> enemy, int coord[] );

private:
   bool isEnemy( Map *map, QList<CubeBasic*> enemy, int x, int y, int z );
};

#endif // HEALAGENT_H
