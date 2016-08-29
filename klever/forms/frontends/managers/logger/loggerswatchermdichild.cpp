#include "loggerswatchermdichild.h"
#include <frameWork/cveManager.h>
#include "../../man.h"

using namespace man;


LoggersWatcherMdiChild::LoggersWatcherMdiChild() {
  // Инициализация сетки расположения графических компонентов
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  QWidget *wgt = getManagerWidget_FromWAPair(tr("logger"),
                                             tr("(LoggerManager)loggersWatcherWidget"));

  grid->addWidget(wgt);
  grid->setContentsMargins(1,1,1,1);
  this->setContentsMargins(1,1,1,1);
  setLayout(grid);
  setWindowTitle("Просмотрщик отчетов");
  setMinimumSize(600,400);
//  setWindowIcon(
//        CveTestSequencesManager::instance().elem()->reportWidget()->viewer->windowIcon() );

}

LoggersWatcherMdiChild::~LoggersWatcherMdiChild() {
}

/*
 * Закрытие окна
 */
void LoggersWatcherMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal( false );
}

