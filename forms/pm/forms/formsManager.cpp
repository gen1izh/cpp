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

    if (Core::Plugins::instance().isPluginExist(tr("analysis"))) {
        connect( getManagerAction_FromWAPair(tr("analysis"),
                                             tr("(PM)BF_AnalizeForm")),
                 SIGNAL(triggered()), this, SLOT(openAnalysisWindow()) );

        if (Core::Plugins::instance().isPluginExist(tr("texteditor"))) {
            connect( getManagerAction_FromActionsList(tr("analysis"),
                                                      tr("(PM)BF_TextEditorOpen")),
                     SIGNAL(triggered()), this, SLOT(openTextEditorWindow()) );

        }

    }

    if (Core::Plugins::instance().isPluginExist(tr("architect"))) {
        connect( getManagerAction_FromWAPair(tr("architect"),
                                             tr("(PM)BF_ArchitectForm")),
                 SIGNAL(triggered()), this, SLOT(openArchitectWindow()) );

        if (Core::Plugins::instance().isPluginExist(tr("texteditor"))) {
            connect( getManagerAction_FromActionsList(tr("architect"),
                                                      tr("(PM)BF_TextEditorOpen")),
                     SIGNAL(triggered()), this, SLOT(openTextEditorWindow()) );

        }
    }

//    if (Core::Plugins::instance().isPluginExist(tr("delpoy"))) {
//        connect( getManagerAction_FromWAPair(tr("project_manager"),
//                                             tr("(PM)BF_DeployBuildForm")),
//                 SIGNAL(triggered()), this, SLOT(openDeployBuildWindow()) );

//    }

    if (Core::Plugins::instance().isPluginExist(tr("document"))) {
        connect( getManagerAction_FromWAPair(tr("document"),
                                             tr("(PM)BF_DocumentsForm")),
                 SIGNAL(triggered()), this, SLOT(openDocumentsWindow()) );

        if (Core::Plugins::instance().isPluginExist(tr("texteditor"))) {
            connect( getManagerAction_FromActionsList(tr("document"),
                                                      tr("(PM)BF_TextEditorOpen")),
                     SIGNAL(triggered()), this, SLOT(openTextEditorWindow()) );

        }

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

    if (Core::Plugins::instance().isPluginExist(tr("project_manager"))) {
        pluginsBar->addAction(getManagerAction_FromWAPair(tr("analysis"), tr("(PM)BF_AnalizeForm")));
        pluginsBar->addAction(getManagerAction_FromWAPair(tr("architect"), tr("(PM)BF_ArchitectForm")));
        // pluginsBar->addAction(getManagerAction_FromWAPair(tr("deploy"), tr("(PM)BF_DeployBuildForm")));
        pluginsBar->addAction(getManagerAction_FromWAPair(tr("document"), tr("(PM)BF_DocumentsForm")));
    }
}

