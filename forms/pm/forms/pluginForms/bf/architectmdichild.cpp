#include "architectmdichild.h"
#include <frameWork/plugins.h>
#include "../../plug.h"

using namespace plug;


ArchitectMdiChild::ArchitectMdiChild() {
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  QWidget *wgt = getManagerWidget_FromWAPair(tr("architect"),
                                             tr("(PM)BF_ArchitectForm"));

  grid->addWidget(wgt);
  grid->setContentsMargins(1,1,1,1);
  this->setContentsMargins(1,1,1,1);
  setLayout(grid);
  setWindowTitle(wgt->windowTitle());
  setWindowIcon(wgt->windowIcon());
  setMinimumSize(1000, 550);

}

ArchitectMdiChild::~ArchitectMdiChild() {
}


void ArchitectMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal(false);
}

