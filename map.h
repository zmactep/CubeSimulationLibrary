#ifndef MAP_H
#define MAP_H

#include "CubeSimulationLibrary_global.h"

#include <stdio.h>

#include "cube.h"

#define max(x,y) (x) > (y) ? (x) : (y)
#define min(x,y) (x) < (y) ? (x) : (y)

struct Point3D
{
  int x, y, z;
};

//!  Maximum view radius.
/*!
  The maximum distanse from the look point to generate new map.
*/
#define MAX_VIEW_RADIUS 5

//!  Map class.
/*!
  The Map of the Simulation. May be real and subjective.
  Has lots of methods towork with it and syncronise maps.
*/
class CUBESIMULATIONLIBRARYSHARED_EXPORT Map
{
private:
  //!  Cubes of the map.
  /*!
    3D array of Cubes, that make the map.
  */
  Cube ***cubes;

  //!  Dimensions of the map.
  /*!
    Number of map levels and dimensions of this levels.
  */
  int levels,
      width,
      height;

  //!  Error flag.
  /*!
    This simple flag is true if something wrong in this map.
  */
  bool error;

public:
  //!  Default constructor.
  /*!
    Creates empty map.
    \sa Map(int, int, int), operator =()
  */
  Map();

  //! Dimensions-based contructor.
  /*!
    Creates the map with given dimensions.
    \param l an integer number of Map`s levels
    \param w an integer width of each level
    \param h an integer height of each level
    Sets up error flag if something wrong with memory.
    \sa Map(), createMap() and operator =()
  */
  Map( int, int, int );

  //! Destructor
  /*!
    Deletes all used memory when the object`s live ends.
    \sa deleteMap()
  */
  ~Map();

  //! Map assignment method.
  /*!
    \param m Map to assign
    \return assigned Map copy
    \sa copyOf()
  */
  Map operator= ( Map );

  //! Map copy method.
  /*!
    \param m pointer to the Map to copy
    \return pointer to the current Map
    \sa operator =()
  */
  Map *copyOf( Map* );

  //! Load one level method.
  /*!
    \param l an integer number of loading level
    \param flags 2D array of transparent flags, must be height*width size
    \return true if there were not any errors and
            false if something wrong had happend
  */
  bool loadLevelMask( int, bool** );

  //! Get submap method.
  /*!
    Gets submap with the given radius around the given reference point.
    \param x an integer x-coordinate of reference Cube
    \param y an integer y-coordinate of reference Cube
    \param z an integer z-coordinate of reference Cube
    \param rad an integer radius
    \return pointer to submap
    \sa appendSubMap()
  */
  Map* getSubMap( int, int, int, int );

  //! Append submap method.
  /*!
    Appends submap to current Map by given reference point and radius around it.
    \param app_map a pointer to submap to append
    \param x an integer x-coordinate of reference Cube
    \param y an integer y-coordinate of reference Cube
    \param z an integer z-coordinate of reference Cube
    \param rad an integer radius
    \return true if there were not any errors and
            false if something wrong had happend
    \sa getSubMap()
  */
  bool appendSubMap( Map*, int, int, int, int );


  //! Get same Cube method.
  /*!
    Returns the Cube in same position as in got Map.
    \param map a Map with got Cube
    \param cube Cube in the same position
    \return Cube or NULL if there are no same Cubes
  */
  Cube* getSameCubeFrom( Map*, CubeBasic* );

  //! Check error method.
  /*!
    \return current error state
    \sa setError()
  */
  bool isError( void );

  //! Set error method.
  /*!
    \return a copy of current map with true error flag
    \sa isError()
  */
  Map setError( void );

  //! Get levels count method.
  /*!
    \return a number of map`s levels
    \sa getHeight(), getWidth()
  */
  int getLevels( void );

  //! Get height method.
  /*!
    \return a map`s height dimension
    \sa getLevels(), getWidth()
  */
  int getHeight( void );

  //! Get width method.
  /*!
    \return a map`s width dimension
    \sa getLevels(), getHeight()
  */
  int getWidth( void );

  // Cube operations

  //! Check Cube transparent method.
  /*!
    \param x an integer x-coordinate of Cube
    \param y an integer y-coordinate of Cube
    \param z an integer z-coordinate of Cube
    \return the transparent flag value of given Cube
  */
  bool isTransparent( int x, int y, int z );

  //! Get Cube infection value method.
  /*!
    \param x an integer x-coordinate of Cube
    \param y an integer y-coordinate of Cube
    \param z an integer z-coordinate of Cube
    \return an infection value of given Cube
  */
  int getInfection( int x, int y, int z );

  //! Cube infection increment method.
  /*!
    \param x an integer x-coordinate of Cube
    \param y an integer y-coordinate of Cube
    \param z an integer z-coordinate of Cube
    \return a new infection value of given Cube
  */
  int incInfection( int x, int y, int z );

  //! Cube infection decrement value method.
  /*!
    \param x an integer x-coordinate of Cube
    \param y an integer y-coordinate of Cube
    \param z an integer z-coordinate of Cube
    \return a new infection value of given Cube
  */
  int decInfection( int x, int y, int z );

  //! Get Cube pointer method.
  /*!
    \param x an integer x-coordinate of Cube
    \param y an integer y-coordinate of Cube
    \param z an integer z-coordinate of Cube
    \return pointer to the given Cube
    \sa getCubeCoord()
  */
  Cube* getCube( int x, int y, int z );

  //! Get Cube coordinates method.
  /*!
    \param cube Cube which coordiantes to find
    \param coord an integer array to put values to, the length must be 3
    \return true if there were not any errors and
            false if something wrong had happend
    \sa getCube()
  */
  bool getCubeCoord( CubeBasic*, int* );

  //! Get transparent Cube count method.
  /*!
    \return number of transparent Cubes in the Map
  */
  int getTransparentCubesCount( void );


  //! Update infection method.
  /*!
    Spread infection into the Map cubes
    \return increment of Map infection
  */
  int updateInfectionState( void );

private:
  //! Create map method.
  /*!
    Creates the map with given dimensions.
    \param l an integer number of map`s levels
    \param w an integer width of each level
    \param h an integer height of each level
    Sets up error flag if something wrong with memory.
    \sa Map(), Map(int, int, int), ~Map(), and operator =()
  */
  bool createMap( int, int, int );

  //! Delete map method.
  /*!
    Deletes all used memory of the Map.
    \sa Map(), Map(int, int, int), ~Map() and operator =()
  */
  void deleteMap();

  //! Get submap coordinates method.
  /*!
    Gets submap with the given radius around
    the given reference point coordinates.
    \param l an integer level number of reference point
    \param x an integer width-coordinate of reference point
    \param y an integer height-coordinate of reference point
    \param rad an integer radius
    \param coord an integer array to put values to, the length must be 6
    \return true if there were not any errors and
            false if something wrong had happend
    \sa getSubMap(), appendSubMap()
  */
  bool getSubMapCoord( int, int, int, int, int* );


  //! Check coordinates method.
  /*!
    \param x an integer x-coordinate of Cube
    \param y an integer y-coordinate of Cube
    \param z an integer z-coordinate of Cube
    \return true if coordinates are in the Map and
            false if not
  */
  bool checkCubeExists( int x, int y, int z );
};

#endif // MAP_H
