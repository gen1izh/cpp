#include "documentsmdichild.h"
#include <frameWork/plugins.h>
#include "../../plug.h"

using namespace plug;


DocumentsMdiChild::DocumentsMdiChild() {
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  QWidget *wgt = getManagerWidget_FromWAPair(tr("document"),
                                             tr("(PM)BF_DocumentsForm"));

  grid->addWidget(wgt);
  grid->setContentsMargins(1,1,1,1);
  this->setContentsMargins(1,1,1,1);
  setLayout(grid);
  setWindowTitle(wgt->windowTitle());
  setWindowIcon(wgt->windowIcon());
  setMinimumSize(1000, 550);

}

DocumentsMdiChild::~DocumentsMdiChild() {
}


void DocumentsMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal(false);
}

