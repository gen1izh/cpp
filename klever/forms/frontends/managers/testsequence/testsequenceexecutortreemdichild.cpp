#include "testsequenceexecutortreemdichild.h"
#include <frameWork/cveManager.h>
#include "../../man.h"

using namespace man;

TestsequenceExecutorMdiChild::TestsequenceExecutorMdiChild() {
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  QWidget *wgt = getManagerWidget_FromWAPair(tr("testsequence"),
                                             tr("(TestSequenceManager)TestsequenceExecutor"));

  grid->addWidget(wgt);
  grid->setContentsMargins(1,1,1,1);
  this->setContentsMargins(1,1,1,1);
  setLayout(grid);
  setWindowTitle("Исполнение тестовой последовательности");
  setMinimumSize(800,400);

  setWindowIcon(wgt->windowIcon());
}

/*
 *
 */
TestsequenceExecutorMdiChild::~TestsequenceExecutorMdiChild() {}

/*
 * Закрытие окна
 */
void TestsequenceExecutorMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  bool isTestStarted = Core::Base::instance().getParameterValue(QString("testStarted"), false);

  if (isTestStarted) {
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"),
                          tr("Идет тест, завершите тест корректно!"));

  } else {
    emit setVisibleSignal(false);
  }

}
