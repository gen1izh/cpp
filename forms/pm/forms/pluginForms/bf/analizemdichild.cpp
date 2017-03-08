#include "analizemdichild.h"
#include <frameWork/plugins.h>
#include "../../plug.h"

using namespace plug;


AnalysisMdiChild::AnalysisMdiChild() {
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  QWidget *wgt = getManagerWidget_FromWAPair(tr("analysis"),
                                             tr("(PM)BF_AnalizeForm"));

  grid->addWidget(wgt);
  grid->setContentsMargins(1,1,1,1);
  this->setContentsMargins(1,1,1,1);
  setLayout(grid);
  setWindowTitle("Анализ требований");
  setWindowIcon(wgt->windowIcon());

}

AnalysisMdiChild::~AnalysisMdiChild() {
}


void AnalysisMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal(false);
}

