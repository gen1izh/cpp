#include "mainwindow.h"

using namespace Core;

/*
 * Создание основных коннекторов приложения
 */
void MainWindow::createConnectors() {

    // Коннекторы управления положением окон в приложении
    connect( closeWindowAct, SIGNAL( triggered() ),
             mdiArea, SLOT( closeActiveSubWindow() ) );
    connect( closeAllWindowsAct, SIGNAL( triggered() ),
             mdiArea, SLOT( closeAllSubWindows() ) );
    connect( tileAct, SIGNAL( triggered() ),
             mdiArea, SLOT( tileSubWindows() ) );
    connect( cascadeAct, SIGNAL( triggered() ),
             mdiArea, SLOT( cascadeSubWindows() ) );

    // Коннекторы для открытия справочной информации
    connect(m_aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));

    foreach(QAction *a, m_documentsApi) {
        connect(a, SIGNAL(triggered()),
                this, SLOT(openDocument()));
    }

}

/*
 * Создание основных действий приложения
 */
void MainWindow::createActions() {

    // Действия управления положением окон в приложении
    closeWindowAct = new QAction(tr("Закрыть"), this );
    closeWindowAct->setStatusTip(tr("Закрыть активное окно") );

    closeAllWindowsAct = new QAction(tr("Закрыть все"), this);
    closeAllWindowsAct->setStatusTip(tr("Закрыть все окна"));

    tileAct = new QAction(QIcon(":/images/tile_vertical.png"), tr("&Последовательно вертикально"), this);
    tileAct->setStatusTip(tr("Окна секциями"));

    cascadeAct = new QAction(QIcon(":/images/cascade.png"), tr("&Каскадом"), this);
    cascadeAct->setStatusTip(tr("Окна каскадом"));

    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);

    m_pluginInformationAction = new QAction(QIcon(":/images/flavour-extended-png/qbic.png"), tr("&Плагины"), this);
    m_pluginInformationAction->setStatusTip(tr("О модулях"));

    // Действия для открытия справочной информации
    m_aboutAction = new QAction( QIcon(":/images/help.png"), tr("&Информация о программе"), this);
    m_aboutAction->setStatusTip( tr( "Информация о системе") );

    // Настройки приложения
    m_settingsAction = new QAction( QIcon(":/settings/img/settings.png"),
                                         tr( "&Настройки..." ),
                                         this );
    m_settingsAction->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_P ) );
    m_settingsAction->setStatusTip( tr( "Окно настроек приложения" ) );

    fillDocumentsActions();

}

/*
 * Создание главного меню приложения
 */
void MainWindow::createMenu() {

    // Меню менеджера форм
    KleverGui::instance().formManager->createMenu();

    QMenu *optionMenu = menuBar()->addMenu(tr("&Опции"));

    optionMenu->addAction(separatorAct);
    optionMenu->addAction(m_settingsAction);

    // Создание меню панелей приложения
    panelMenu = menuBar()->addMenu(tr("&Панели"));

    // Создание меню работы с окнами приложения
    windowMenu = menuBar()->addMenu(tr("&Окна"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Помощь"));
    helpMenu->addAction(m_pluginInformationAction);
    helpMenu->addSeparator();
    helpMenu->addAction(m_aboutAction);


    QMenu *helpDocumentsMenu = helpMenu->addMenu(tr("&Документация"));
    helpDocumentsMenu->addActions(m_documentsApi);

    // Создание меню работы с окнами приложения
    updateActivWindowsListOnMenu();

}

/*
 * Создание панели быстрого запуска приложения
 */
void MainWindow::createToolBars() {

    // Создание главного меню быстрого запуска. Права доступа определяются внутри
    KleverGui::instance().formManager->createToolBar();

    // Создание панели работы с окнами
    windowToolBar = addToolBar(tr("Окна"));
    windowToolBar->setObjectName("Окна");
    windowToolBar->setIconSize(QSize(32,32));
    windowToolBar->addAction(tileAct);
    windowToolBar->addAction(cascadeAct);

    // TODO: CAN_SEE_APP_SETTINGS
    //  if (Managers::instance().boot()->hasRightUser(CAN_SEE_APP_SETTINGS)) {
    QToolBar *toolsToolBar = addToolBar(tr("Инструменты"));
    toolsToolBar->setObjectName("Инструменты");
    toolsToolBar->setIconSize(QSize(32,32));
    toolsToolBar->addAction(m_settingsAction);
    //  }

    // Создание панели справки
    QToolBar *helpToolBar = KleverGui::instance().mainwindow()->addToolBar(tr("Помощь"));
    helpToolBar->setObjectName("Помощь");
    helpToolBar->setIconSize(QSize(32,32));

    helpToolBar->addAction(m_pluginInformationAction);
    helpToolBar->addAction(m_aboutAction);

}

/*
 * Создание доков окон
 */
void MainWindow::createDockWindows() {

    // Инициализация нижней панели главного окна приложения. Панель активных окон.
    QDockWidget *minimizedBottomDock = new QDockWidget(tr("Активные окна"), this);
    minimizedBottomDock->setObjectName("Активные окна");
    minimizedBottomDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    minimizedBottomDock->setWidget(KleverGui::instance().activWindowsListToolBar);
    minimizedBottomDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addDockWidget(Qt::BottomDockWidgetArea, minimizedBottomDock, Qt::Vertical);
    panelMenu->addAction(minimizedBottomDock->toggleViewAction());

    KleverGui::instance().formManager->createDocks(docksList);

    //  foreach (QPair<QDockWidget*,QPair<int,int> > dock, docksList) {
    //    dock->first->setParent(KleverGui::instance().mainwindow());
    //    addDockWidget(dock->second.first,dock, dock->second.second);
    //    panelMenu->addAction(dock->toggleViewAction());
    //  }

    for (int i = 0; i < docksList.size(); i++) {
        QPair<QDockWidget*,QPair<int,int> > dock = docksList.at(i);
        dock.first->setParent(KleverGui::instance().mainwindow());
        addDockWidget((Qt::DockWidgetArea)dock.second.first,
                      dock.first,
                      (Qt::Orientation)dock.second.second);
        panelMenu->addAction(dock.first->toggleViewAction());
    }

    //TODO: CAN_SEE_MODULES_ALL_CONTROLS
    //  if (Managers::instance().boot()->hasRightUser(CAN_SEE_MODULES_ALL_CONTROLS)) {

    //    //Если список модулей не пуст, то рисуем правый док с индикаторами, иначе он не нужен.
    //    if (!ModulesManager::instance().modules().isEmpty()) {

    //      // Инициализация правой панели приложения. Индикаторы модулей
    //      QWidget     *wgt = NULL;
    //      QHashIterator<QString,QList<ModulesQueueItem> >  i(
    //                  ModulesManager::instance().modules());
    //      while (i.hasNext()) {
    //        i.next();
    //        QWidget     *indicatorsWidget = new QWidget();
    //        QVBoxLayout *indicators = new QVBoxLayout();
    //        bool         isWidgets = false;
    //        for ( int j = 0; j < i.value().size(); j++ ) {
    //          if ( i.value().at(j).isNeedUse ) {
    //            wgt = i.value().at(j).i->getIndicatorsPanelWidget();
    //            if (wgt == NULL) {
    //              continue;
    //            } else {
    //              indicators->addWidget(wgt);
    //              isWidgets = true;
    //            }
    //          }
    //        }

    //      indicatorsWidget->setLayout(indicators);
    //      indicators->setAlignment(Qt::AlignTop);

    //        if ( isWidgets ) {
    //          QDockWidget *dock = new QDockWidget(i.value().at(0).i->getModuleName(), this);
    //          dock->setObjectName(i.value().at(0).i->getModuleName());
    //          dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea );
    //          dock->setWidget(indicatorsWidget);
    //          addDockWidget(Qt::RightDockWidgetArea, dock);
    //          indicatorPanelMenu->addAction(dock->toggleViewAction());
    //        }
    //      }
    //    }
    //    else {
    //      Library::LoggerApi::logWarning(this,"Список модулей пуст!");
    //    }
    //  }
}
