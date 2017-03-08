#include "loggerswatchermdichild.h"
#include <frameWork/plugins.h>
#include "../../plug.h"

using namespace plug;


LoggersWatcherMdiChild::LoggersWatcherMdiChild() {
  // Инициализация сетки расположения графических компонентов
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  QWidget *wgt = getManagerWidget_FromWAPair(tr("logger"),
                                             tr("(Logger)Watcher"));

  grid->addWidget(wgt);
  grid->setContentsMargins(1,1,1,1);
  this->setContentsMargins(1,1,1,1);
  setLayout(grid);
  setWindowTitle("Просмотрщик отчетов");
  setMinimumSize(800,400);
  setWindowIcon(wgt->windowIcon());

}

LoggersWatcherMdiChild::~LoggersWatcherMdiChild() {
}

/*
 * Закрытие окна
 */
void LoggersWatcherMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal(false);
}

