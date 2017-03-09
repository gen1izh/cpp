#include "deploybuildmdichild.h"
#include <frameWork/plugins.h>
#include "../../plug.h"

using namespace plug;


DeployBuildMdiChild::DeployBuildMdiChild() {
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  QWidget *wgt = getManagerWidget_FromWAPair(tr("project_manager"),
                                             tr("(PM)BF_DeployBuildForm"));

  grid->addWidget(wgt);
  grid->setContentsMargins(1,1,1,1);
  this->setContentsMargins(1,1,1,1);
  setLayout(grid);
  setWindowTitle(wgt->windowTitle());
  setWindowIcon(wgt->windowIcon());
  setMinimumSize(1000, 550);
}

DeployBuildMdiChild::~DeployBuildMdiChild() {
}

void DeployBuildMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal(false);
}

