#ifndef CUBESIMULATIONWIDGET_H
#define CUBESIMULATIONWIDGET_H

#include "CubeSimulationLibrary_global.h"

#include <QtGui>

#include "map.h"
#include "environment.h"

#include "cubesimulationview.h"

//!  CubeSimulationWidget class.
/*!
  A main window of the simulation application.
*/
class CUBESIMULATIONLIBRARYSHARED_EXPORT CubeSimulationWidget : public QWidget
{
  Q_OBJECT

private:
  //! Simulation view.
  /*!
    A subwindow, where the simulation will be showed.
  */
  CubeSimulationView *wgtGL;

  //! Environment of the simulation.
  /*!
    The Environment where the simulation will be.
  */
  Environment *env;

  //! Map of simulation.
  /*!
    This Map is the most real, that connects with the Environment
    and CubeSimulationView.
  */
  Map *map;


  //! Toggle button.
  /*!
    This button toggles simulation.
  */
  QPushButton *toggleButton;

public:
  //! Constructor.
  /*!
    Creates the interface and Environment for the simulation.
    \param parent a parent object
  */
  CubeSimulationWidget(QWidget *parent = 0);


  //! Constructor.
  /*!
    Creates the interface and Environment for the simulation.
    Map will be genered from the file, Agents will be same a AMF type.
    \param mapFile filename for Map load
    \param facts AgentManagerFactorys for simulation
    \param amCount number of teams
    \param afacts factories to create Agents in the teams
    \param aCount number of Agents per Team
    \param parent a parent object
  */
  CubeSimulationWidget(QString mapFile, AgentManagerFactory *facts = NULL, int amCount = 0,
                                        AgentFactory *afacts = NULL, int aCount = 0,
                                        QWidget *parent = 0);

  //! Destructor.
  /*!
    Deletes all used memory when the object`s live ends.
  */
  ~CubeSimulationWidget();

protected:
  //! Key press listener.
  void keyPressEvent( QKeyEvent *event );

public slots:
  //! Toggle buttun slot
  /*!
    Toggles simulation and changes text on a Toggle button.
  */
  void slot_toggleSimulation( void );

private:
  //! Init Environment method
  /*!
    Inits the Environment, creates the Map with the given dimensions
    and connects them.
    \param l an integer number of Map`s levels
    \param w an integer width of each level
    \param h an integer height of each level
  */
  void initEnvironment( int l, int w, int h );

  //! Init method.
  /*!
    Inits some stuff for widget working.
  */
  void init( void );
};

#endif // CUBESIMULATIONWIDGET_H
