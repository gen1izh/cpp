#include "formsManager.h"
#include <frameWork/gui/mainwindow/mainwindow.h>
#include "man.h"

using namespace man;

/*
 * Инициализация журнала приложения
 */
QDockWidget *FormsManager::createLoggerDock() {
  loggerBottomDock = new QDockWidget(tr("Журналы"));

  loggerBottomDock->setObjectName("Журналы");
  loggerBottomDock->setAllowedAreas(Qt::BottomDockWidgetArea);

  QWidget *wgt = getLoggerWidget_FromWAPair(tr("(LoggerManager)loggersTabsWidgets"));

  wgt->setParent(loggerBottomDock);
  loggerBottomDock->setWidget(wgt);

  loggerBottomDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
  loggerBottomDock->setMinimumHeight(50);  /* todo: magic number */
  loggerBottomDock->setMaximumHeight(150); /* todo: magic number */

  return loggerBottomDock;
}


/*
 * Инициализация доков менеджера тестовых последовательностей
 */
QDockWidget *FormsManager::createTestsequenceManagerDock() {

  leftDock = new QDockWidget(tr("Навигация"));
  leftDock->setObjectName("Навигация");

  leftDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  QWidget *wgt = getManagerWidget_FromWAPair(tr("testsequence"),

                                             tr("(TestSequenceManager)TestsequenceTestsViewer"));

  wgt->setParent(leftDock);
  leftDock->setWidget(wgt);

  leftDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

  return leftDock;

}

/*
 * Создание доков приложения
 */
void FormsManager::createDocks(QList<QPair<QDockWidget*,QPair<int,int> > > &docksList) {

  QPair<QDockWidget*,QPair<int,int> > p;

  // INFO: Поскольку docks создавали лишь менеджеры активно, то
  // разделения на функции содания docks модулей и менеджеров тут нет.

  if (Core::CveManager::instance().isManagerExist(tr("logger"))) {
    p.first = createLoggerDock();
    p.second.first  = Qt::BottomDockWidgetArea;
    p.second.second = Qt::Horizontal;
    docksList.append(p);
  }

  if (Core::CveManager::instance().isManagerExist(tr("testsequence"))) {
    p.first = createTestsequenceManagerDock();
    p.second.first  = Qt::LeftDockWidgetArea;
    p.second.second = Qt::Vertical;
    docksList.append(p);
  }

}
