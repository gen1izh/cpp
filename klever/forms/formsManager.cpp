#include "formsManager.h"
#include <frameWork/gui/klevergui.h>
#include <frameWork/plugins.h>

#include "plug.h"

using namespace plug;

FormsManager::FormsManager() {
    setObjectName(tr("Менеджер форм"));  // Установка имени модуля
    createActions();                     // Создание действий
    createConnections();                 // Создание соединений
}


void FormsManager::createConnections() {
    if (Core::Plugins::instance().isPluginExist(tr("logger"))) {
        connect( getManagerAction_FromWAPair(tr("logger"),
                                             tr("(Logger)Watcher")),
                 SIGNAL(triggered()), this, SLOT(openLoggersWatcherWindow()) );
    }
}


/*
 * Создание действий
 */
void FormsManager::createActions() {

}


/*
 * Создание dock
 */
void FormsManager::createDocks(QList<QPair<QDockWidget*,QPair<int,int> > > &docksList) {

    QPair<QDockWidget*,QPair<int,int> > p;

    if (Core::Plugins::instance().isPluginExist(tr("logger"))) {
        m_loggerDock = new QDockWidget(tr("Журнал"));

        m_loggerDock->setObjectName("Журнал");
        m_loggerDock->setAllowedAreas(Qt::BottomDockWidgetArea);

        QWidget *wgt = getLoggerWidget_FromWAPair(tr("(Logger)LoggerForm"));

        wgt->setParent(m_loggerDock);
        m_loggerDock->setWidget(wgt);

        m_loggerDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
        m_loggerDock->setMinimumHeight(50);  /* todo: magic number */

        p.first = m_loggerDock;
        p.second.first  = Qt::BottomDockWidgetArea;
        p.second.second = Qt::Horizontal;
        docksList.append(p);
    }
}


/*
 * Создает меню
 */
void FormsManager::createMenu() {
    if (Core::Plugins::instance().isPluginExist(tr("logger"))) {
        QMenu *loggerMenu = Core::KleverGui::instance().mainwindow()->menuBar()->addMenu(tr("&Журнал"));
        loggerMenu->addAction(getManagerAction_FromWAPair("logger", "(Logger)Watcher"));
    }
}


/*
 * Создает toolbar
 */
void FormsManager::createToolBar() {
    QToolBar *pluginsBar = Core::KleverGui::instance().mainwindow()->addToolBar(tr("Плагины"));
    pluginsBar->setObjectName("Плагины");
    pluginsBar->setIconSize(QSize(32,32));

    if (Core::Plugins::instance().isPluginExist(tr("logger"))) {
      pluginsBar->addAction(getManagerAction_FromWAPair(tr("logger"), tr("(Logger)Watcher")));
    }
}

