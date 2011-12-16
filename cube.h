#ifndef CUBE_H
#define CUBE_H

#include "cubebasic.h"

//!  Cube class.
/*!
  Trivial building block of the Map.
*/
class Cube : public CubeBasic
{
public:
  //! Constructor.
  /*!
    Constructs object setting default values:
    no infection and positive transparent.
  */
  Cube()
  {
    infection = 0;
    transparent = true;
  }

  //! Set transparent method.
  /*!
    \param t a bool value of new transparent
    \return new transparent flag value
    \sa isTransparent()
  */
  inline bool setTransparent( bool t )
  {
    return transparent = t;
  }

  //! Set infection method.
  /*!
    \param i an integer value of new infection
    \return new infection value
    \sa incInfection(), decInfection() and getInfection()
  */
  inline int setInfection( int i )
  {
    if(i > MAX_INFECTION)
      i = MAX_INFECTION;
    return infection = i;
  }

  //! Cube assignment method.
  /*!
      \param c Cube to assign
      \return assigned Cube copy
    */
  inline Cube operator=( Cube c )
  {
    transparent = c.transparent;
    infection = c.infection;

    return *this;
  }
};

#endif // CUBE_H
