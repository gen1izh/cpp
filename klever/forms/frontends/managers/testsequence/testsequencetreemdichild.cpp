#include "testsequencetreemdichild.h"
#include <frameWork/cveManager.h>
#include "../../man.h"

using namespace man;

TestSequenceMdiChild::TestSequenceMdiChild() {
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  QWidget *wgt = getManagerWidget_FromWAPair(tr("testsequence"),
                                             tr("(TestSequenceManager)TestsequenceEditor"));

  grid->addWidget(wgt);
  grid->setContentsMargins(1,1,1,1);
  this->setContentsMargins(1,1,1,1);
  setLayout(grid);
  setWindowTitle("Редактор");
  setMinimumSize(800,400);

  setWindowIcon(wgt->windowIcon());
}

/*
 *
 */
TestSequenceMdiChild::~TestSequenceMdiChild() {}

/*
 * Закрытие окна
 */
void TestSequenceMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal(false);
}
