#include "map.h"

Map::Map()
{
  width = height = levels = 0;
  cubes = NULL;
  error = false;
}


Map::Map( int l, int w, int h )
{
  createMap(l, w, h);
}

Map::~Map()
{
  deleteMap();
}

Map Map::operator= (Map m)
{
  deleteMap();
  createMap(m.levels, m.width, m.height);

  for( int i = 0; i < levels; i++ )
    for( int j = 0; j < height; j++ )
      for( int k = 0; k < width; k++ )
      {
        cubes[i][j][k].setInfection(m.cubes[i][j][k].getInfection());
        cubes[i][j][k].setTransparent(m.cubes[i][j][k].isTransparent());
      }

  return *this;
}

Map *Map::copyOf( Map* m )
{
  deleteMap();

  if(!m)
    return NULL;

  createMap(m->levels, m->width, m->height);

  for( int i = 0; i < levels; i++ )
    for( int j = 0; j < height; j++ )
      for( int k = 0; k < width; k++ )
      {
        cubes[i][j][k].setInfection(m->cubes[i][j][k].getInfection());
        cubes[i][j][k].setTransparent(m->cubes[i][j][k].isTransparent());
      }

  return this;
}

bool Map::loadLevelMask( int l, bool** flags )
{
  if(l < 0 || l >= levels)
    return false;

  for( int i = 0; i < height; i++ )
    for( int j = 0; j < width; j++ )
      cubes[l][i][j].setTransparent(!flags[i][j]);

  return true;
}

Map* Map::getSubMap( int x, int y, int z, int rad )
{
  int coord[6];
  if(!getSubMapCoord(x,y,z,rad,coord))
    return NULL;

  // Set transparent and infection in new map
  Map *map = new Map(coord[5] - coord[4],
                     coord[3] - coord[2],
                     coord[1] - coord[0]);

  for( int i = coord[4]; i < coord[5]; i++ )
    for( int j = coord[2]; j < coord[3]; j++ )
      for( int k = coord[0]; k < coord[1]; k++ )
      {
        map->cubes[i-coord[4]][j-coord[2]][k-coord[0]].setTransparent(
                                            cubes[i][j][k].isTransparent());
        map->cubes[i-coord[4]][j-coord[2]][k-coord[0]].setInfection(
                                            cubes[i][j][k].getInfection());
      }

  return map;
}

bool Map::appendSubMap( Map* app_map,
                        int x, int y, int z, int rad )
{
  int coord[6];
  if(!getSubMapCoord(x,y,z,rad,coord))
    return false;

  for( int i = coord[4]; i < coord[5]; i++ )
    for( int j = coord[2]; j < coord[3]; j++ )
      for( int k = coord[0]; k < coord[1]; k++ )
      {
        cubes[i][j][k].setTransparent(app_map->cubes[i-coord[04]][j-coord[2]][k-coord[0]].isTransparent());
        cubes[i][j][k].setInfection(app_map->cubes[i-coord[04]][j-coord[2]][k-coord[0]].getInfection());
      }

  return true;
}

Cube* Map::getSameCubeFrom( Map* map, CubeBasic* cube )
{
  if(levels != map->levels &&
     width  != map->width &&
     height != map->height)
    return NULL;

  int coord[3];

  if(!map->getCubeCoord(cube, coord))
    return NULL;

  return getCube(coord[0], coord[1], coord[2]);
}

bool Map::getCubeCoord( CubeBasic* cube, int *coord )
{
  for( int i = 0; i < levels; i++ )
    for( int j = 0; j < height; j++ )
      for( int k = 0; k < width; k++ )
        if(cube == &cubes[i][j][k])
        {
          *(coord) = k;
          *(coord + 1) = i;
          *(coord + 2) = j;

          return true;
        }

  return false;
}

int Map::getTransparentCubesCount( void )
{
  int num = 0;

  for( int i = 0; i < levels; i++ )
    for( int j = 0; j < height; j++ )
      for( int k = 0; k < width; k++ )
        if(cubes[i][j][k].isTransparent())
          num++;

  return num;
}

bool Map::createMap( int l, int w, int h )
{
  width = w;
  height = h;
  levels = l;
  error = false;

  cubes = new Cube**[levels];
  if(!cubes)
  {
    error = true;
    return !error;
  }

  for( int i = 0; i < levels; i++ )
  {
    cubes[i] = new Cube*[height];
    if(!cubes[i])
    {
      error = true;
      return !error;
    }

    for( int j = 0; j < height; j++ )
    {
      cubes[i][j] = new Cube[width];
      if(!cubes[i][j])
      {
        error = true;
        return !error;
      }

      for( int k = 0; k < width; k++ )
      {
        cubes[i][j][k].setInfection(0);
        cubes[i][j][k].setTransparent(true);
      }
    }
  }

  return !error;
}

void Map::deleteMap()
{
  if(cubes == NULL)
    return;

  for( int i = 0; i < levels; i++ )
  {
    for( int j = 0; j < height; j++ )
    {
      if(cubes[i][j])
        delete[] cubes[i][j];
    }
    if(cubes[i])
      delete[] cubes[i];
  }

  delete[] cubes;
  cubes = NULL;
}

bool Map::getSubMapCoord( int x, int y, int z, int rad, int* coord)
{
  if(!checkCubeExists(x,y,z))
    return false;

  if(rad > MAX_VIEW_RADIUS)
    rad = MAX_VIEW_RADIUS;


  // Get distanse in each direction
  int dir_nord,           //
      dir_south,          //  w-1  w+1
      dir_west,           //    w n e   h-1
      dir_east,           //      s     h+1
      dir_up,             //  u l-1
      dir_down;           //  d l+1

  dir_nord = z - rad >= 0 ? rad : z;
  dir_south = z + rad <= height - 1 ? rad : (height - 1) - z;

  dir_west = x - rad >= 0 ? rad : x;
  dir_east = x + rad <= width - 1 ? rad : (width - 1) - x;

  dir_up = y - rad >= 0 ? rad : y;
  dir_down = y + rad <= levels - 1 ? rad : (levels - 1) - y;

  // Get 2 charactristic points of Map
  *coord = x - dir_west;
  *(coord + 1) = x + dir_east;

  *(coord + 2) = z - dir_nord;
  *(coord + 3) = z + dir_south;

  *(coord + 4) = y - dir_up;
  *(coord + 5) = y + dir_down;

  return true;
}

int Map::updateInfectionState( void )
{
  int counter = 0;

  for( int y = 0; y < levels; y++ )
    for( int z = 0; z < height; z++ )
      for(  int x = 0; x < width; x++ )
      {
        int infection = getInfection(x, y, z);
        if(infection < MAX_INFECTION)
          continue;

        Cube *cube;

        for( int i = -1; i < 2; i++ )
          for( int j = -1; j < 2; j++ )
            for( int k = -1; k < 2; k++ )
            {
              if(!i &&!j && !k)
                continue;

              cube = getCube(x+k, y+i, z+j);
              if(cube && !cube->isTransparent())
              {
                int inf = cube->getInfection();
                counter += cube->incInfection() - inf;
              }
            }

        getCube(x,y,z)->setInfection(0);
        getCube(x,y,z)->setTransparent(true);
      }

  return counter;
}
