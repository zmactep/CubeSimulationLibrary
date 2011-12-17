#ifndef CUBEBASIC_H
#define CUBEBASIC_H

#include "CubeSimulationLibrary_global.h"

#include <stdio.h>

//! Maximum infection.
/*!
  Maximum possible infection of one CubeBasic.
*/
#define MAX_INFECTION       8

//!  CubeBasic class.
/*!
  Trivial building block of the Map. Basic version for agents.
*/
class CUBESIMULATIONLIBRARYSHARED_EXPORT CubeBasic
{
protected:
  //! Infection value.
  /*!
    Current infection value of this Cube.
  */
  int infection;

  //! Transparent flag.
  /*!
    If transparent flag is true, than any Agent can stay in it.
  */
  bool transparent;

public:
  //! Constructor.
  /*!
    Constructs object setting default values:
    no infection and positive transparent.
  */
  CubeBasic()
  {
    infection = 0;
    transparent = true;
  }

  //! Infection increment method.
  /*!
      \return new infection value
      \sa decInfection() and getInfection()
    */
  inline int incInfection( void )
  {
    return infection < MAX_INFECTION ? ++infection : infection;
  }

  //! Infection decrement method.
  /*!
      \return new infection value
      \sa incInfection() and getInfection()
    */
  inline int decInfection( void )
  {
    return infection > 0 ? --infection : infection;
  }

  //! Get current infection value method.
  /*!
      \return current infection value
      \sa incInfection() and decInfection()
    */
  inline int getInfection( void )
  {
    return infection;
  }

  //! Get current transparent flag value method.
  /*!
      \return current transparent flag value
    */
  inline bool isTransparent( void )
  {
    return transparent;
  }

  //! CubeBasic assignment method.
  /*!
      \param c CubeBasic to assign
      \return assigned CubeBasic copy
    */
  inline CubeBasic operator=( CubeBasic c )
  {
    transparent = c.transparent;
    infection = c.infection;

    return *this;
  }
};

#endif // CUBEBASIC_H
