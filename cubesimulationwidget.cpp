#include "cubesimulationwidget.h"

CubeSimulationWidget::CubeSimulationWidget(QWidget *parent)
  : QWidget(parent)
{
  initEnvironment(5,5,5);

  init();
}

CubeSimulationWidget::CubeSimulationWidget(QString mapFile, AgentManagerFactory *facts,
                                           int amCount, AgentFactory *afacts,
                                           int aCount, QWidget *parent)
{
  QFile fileMap(mapFile);
  bool flag = false;


  if(fileMap.open(QFile::ReadOnly)) {
    QStringList line;

    line = QString("").append(fileMap.readLine()).split(" ");

    if(line.length() < 3)
      flag = true;
    else {
      int l, w, h;

      l = line.at(0).toInt();
      w = line.at(1).toInt();
      h = line.at(2).toInt();

      map = new Map(l,w,h);

      bool **level;
      level = new bool*[h];
      for( int i = 0; i < h; i++ )
        level[i] = new bool[w];

      QString oneLine;
      for( int i = 0; i < l; i++ ) {
        for( int j = 0; j < h; j++ ) {
          oneLine = fileMap.readLine();
          for( int k = 0; k < w; k++ )
            level[j][k] = (oneLine.at(k).toAscii() - '0');
        }
        map->loadLevelMask(i, level);
      }

      env = new Environment(map, facts, amCount, afacts, aCount);
    }
  }
  else
    flag = true;


  if(flag) {
    initEnvironment(5,5,5);
  }

  init();
}


CubeSimulationWidget::~CubeSimulationWidget()
{
  env->terminate();
  if(env)
    delete env;
  env = NULL;
}

void CubeSimulationWidget::initEnvironment( int l, int w, int h )
{
  AgentManagerFactory facts[2];

  map = new Map(l,w,h);
  env = new Environment(map, facts, 2);

  // Generate map here
  map->getCube(0,0,0)->setTransparent(false);

  map->getCube(0,1,0)->setTransparent(false);
  map->getCube(0,1,0)->setInfection(5);

  map->getCube(0,2,0)->setTransparent(false);
  map->getCube(0,2,0)->setInfection(1);
}

void CubeSimulationWidget::slot_toggleSimulation( void )
{
  env->slot_toggleStart();
  if(env->isStarted())
    toggleButton->setText("Pause");
  else
    toggleButton->setText("Start");
}

void CubeSimulationWidget::init( void )
{
  QVBoxLayout *play = new QVBoxLayout(this);

  wgtGL = new CubeSimulationView(this);
  wgtGL->loadEnvironment(env);

  connect(env, SIGNAL(stateChanged()), wgtGL, SLOT(updateGL()));

  QHBoxLayout *playControls = new QHBoxLayout(this);
  toggleButton = new QPushButton(tr("Start"), this);
  QPushButton *clearButtor = new QPushButton(tr("Clear"), this);
  QPushButton *exitButton = new QPushButton(tr("Exit"), this);

  connect(toggleButton, SIGNAL(clicked()), this, SLOT(slot_toggleSimulation()));
  connect(exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

  playControls->addWidget(toggleButton);
  playControls->addWidget(clearButtor);
  playControls->addWidget(exitButton);

  play->addWidget(wgtGL);
  play->addLayout(playControls);

  setLayout(play);
}
