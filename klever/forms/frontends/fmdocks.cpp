#include "formsManager.h"
#include <frameWork/gui/mainwindow/mainwindow.h>
#include "plug.h"

using namespace plug;

/*
 * Инициализация журнала приложения
 */
QDockWidget *FormsManager::createLoggerDock() {
  loggerBottomDock = new QDockWidget(tr("Журнал"));

  loggerBottomDock->setObjectName("Журнал");
  loggerBottomDock->setAllowedAreas(Qt::BottomDockWidgetArea);

  QWidget *wgt = getLoggerWidget_FromWAPair(tr("(Logger)LoggerForm"));

  wgt->setParent(loggerBottomDock);
  loggerBottomDock->setWidget(wgt);

  loggerBottomDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
  loggerBottomDock->setMinimumHeight(50);  /* todo: magic number */

  return loggerBottomDock;
}


/*
 * Инициализация доков плагина тестовых последовательностей
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
  // разделения на функции содания docks модулей и плагинов тут нет.

  if (Core::Plugins::instance().isPluginExist(tr("logger"))) {
    p.first = createLoggerDock();
    p.second.first  = Qt::BottomDockWidgetArea;
    p.second.second = Qt::Horizontal;
    docksList.append(p);
  }

  if (Core::Plugins::instance().isPluginExist(tr("testsequence"))) {
    p.first = createTestsequenceManagerDock();
    p.second.first  = Qt::LeftDockWidgetArea;
    p.second.second = Qt::Vertical;
    docksList.append(p);
  }

}
