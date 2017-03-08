#include "mainwindow.h"

#include <frameWork/information.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    setupStyleAndMainSettings();

    // Установка mdi area
    initializeMdiArea();
    setMapper();
    setCentralWidget(mdiArea);

    // Печать в панель статуса
    statusBar()->showMessage(tr("Приложение запущено!"));

    setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowNestedDocks
                   | QMainWindow::AllowTabbedDocks);

}

MainWindow::~MainWindow() {
}

/*
 *  Настройка основных настроек приложения и стиля
 */
void MainWindow::setupStyleAndMainSettings()
{
    // Установка имени главного модуля
    setObjectName(QString("ГП - mainwindow"));

    QString sessionName = Core::Base::instance().getParameterValue(QString("[Session]Name"),
                                                                   QString(""));

    QString user = Core::Base::instance().getParameterValue(QString("[Autorization]User"),
                                                            QString(""));
    // Установка названия главной формы
    QString title = QString("%1 [PID = %2 ] [%3:%4]")
            .arg(Information::instance().mainTitleApp())
            .arg(QApplication::applicationPid())
            .arg(sessionName)
            .arg(user);

    setWindowTitle(title);

    QApplication::setStyle(QStyleFactory::create(Information::instance().style()));
}


/*
 * Закрытие основного окна приложения
 */
void MainWindow::closeEvent( QCloseEvent *event ) {
    mdiArea->closeAllSubWindows();
    event->accept();

    QSettings settings(Information::instance().company(),
                       QString("%1_%2").arg(Information::instance().mainTitleApp())
                       .arg(Information::instance().version()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}


/*
 * Признак того что форма видима и активна
 */
QWidget *MainWindow::isVisibleAndActiveMdiChild() {
    if ( QMdiSubWindow *activeSubWindow = Core::KleverGui::instance().mdi()->activeSubWindow() ) {
        if ( activeSubWindow->isVisible() ) {
            return qobject_cast<QWidget *>(activeSubWindow->widget());
        }
    }
    return 0;
}


/*
 * Добавление в панель активных окон пунктов соответствующих открытых окон
 */
void MainWindow::updateActivWindowsListOnToolBar() {
    // Очистка панели активных окон
    Core::KleverGui::instance().activWindowsListToolBar->clear();

    // Получение списка всех окон из subWindowList
    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();

    Core::KleverGui::instance().activWindowsListToolBar->setToolButtonStyle(
                Qt::ToolButtonTextBesideIcon );

    // TODO: при обращении к элементам QList необходима проверка на его пределы
    // Поиск видимы окон и добавление их в панель активных окон
    for ( int i = 0; i < windows.size(); ++i ) {
        if ( (windows.at(i)->isVisible()) || (windows.at(i)->isMinimized()) ) {
            QWidget *child  = qobject_cast<QWidget *>(windows.at(i)->widget());
            // Создание действия
            QAction   *action =
                    Core::KleverGui::instance().activWindowsListToolBar->addAction(
                        windows.at(i)->windowIcon(),
                        windows.at(i)->widget()->windowTitle() );

            action->setCheckable( true );

            action->setChecked(
                        child == isVisibleAndActiveMdiChild() );

            if  ( ( child == isVisibleAndActiveMdiChild() )
                  /* || ( child->isMinimized() )*/ ) {
                windows.at(i)->setWindowState(windows.at(i)->windowState() & ~Qt::WindowMinimized);
                windows.at(i)->setVisible(true);
            }

            // Установка события на действие
            connect( action, SIGNAL( triggered() ), windowMapper, SLOT( map() ) );

            // Установка события на действие
            connect( action, SIGNAL( triggered() ), this,
                     SLOT( updateActivWindowsListOnToolBar() ) );

            windowMapper->setMapping( action, windows.at(i) );
        }
    }
}

/*
 * Добавление в меню "Окна" пунктов соответствующих открытых окон
 * TODO: Надо updateActivWindowsListOnToolBar и updateActivWindowsListOnMenu
 * объединить.
 */
void MainWindow::updateActivWindowsListOnMenu() {

    windowMenu->clear();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(closeWindowAct);
    windowMenu->addAction(closeAllWindowsAct);
    windowMenu->addSeparator();
    windowMenu->addAction(separatorAct);

    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();

    separatorAct->setVisible(!windows.isEmpty());

    for ( int i = 0; i < windows.size(); ++i ) {
        if ( windows.at(i)->isVisible() ) {
            QWidget *child  = qobject_cast<QWidget *>(windows.at(i)->widget());
            QAction   *action = windowMenu->addAction(
                        windows.at(i)->widget()->windowTitle() );
            action->setCheckable( true );
            action->setChecked(
                        child == isVisibleAndActiveMdiChild() );

            connect( action, SIGNAL( triggered() ), windowMapper, SLOT( map() ) );

            windowMapper->setMapping( action, windows.at(i) );
        }
    }
}

/*
 * Заполнить пункты меню документации
 */
void MainWindow::fillDocumentsActions() {
    QDir dir;
    dir.setPath(QApplication::applicationDirPath() + "/doc");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QAction *act = new QAction(fileInfo.fileName(),
                                   this );
        act->setObjectName(fileInfo.fileName());
        m_documentsApi.append(act);
    }
}


/*
 * Открытие документации с описанием функций скриптов
 */
void MainWindow::openDocument() {

    QString fileName = QApplication::applicationDirPath() + "/doc/"
            + QObject::sender()->objectName();
    QFileInfo file(fileName);

    if (file.exists()) {
        QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(fileName)));
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Проблемы с открытием файла! Проверьте наличие файла.");
        msgBox.exec();
    }
}

/*
 * Краткое описание программы
 */
void MainWindow::about() {
    QString msg;

    msg = QString("%1 %2 \n %3")
            .arg(Information::instance().aboutMessageTop())
            .arg(Information::instance().version())
            .arg(Information::instance().aboutMessageBottom());

    QMessageBox::about( NULL,
                        QString("%1 %2")
                        .arg(Information::instance().aboutMessageTitle())
                        .arg(Information::instance().version()),
                        msg );
}


