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

/*
 *  Настройка основных настроек приложения и стиля
 */
void MainWindow::setupStyleAndMainSettings()
{
  AppSetupApi  appsetup;
  bool ok;
  // Проверка наличия основных параметров приложения
  appsetup.checkApplicationParam(QString("Main"), QString("/name"),  tr("ГП - mainwindow"));
  appsetup.checkApplicationParam(QString("Main"), QString("/text"),  Information::instance().mainTitleApp());
  appsetup.checkApplicationParam(QString("Main"), QString("/style"), QString("%1").arg(QPLASTIQUESTYLE));
  appsetup.checkApplicationParam(QString("Main"), QString("/mode"),  QString("off"));

  QString sessionName = Cve::instance().getParameterValue(QString("/sessionName"),QString());
  QString rights      = Cve::instance().getParameterValue(QString("/rights"),QString());

  // Установка имени главного модуля
  setObjectName(appsetup.getApplicationParam(QString("Main"), QString("/name")));
  // Установка названия главной формы
  QString title = QString("%1 [PID = %2 ] [%3:%4]")
                  .arg(appsetup.getApplicationParam(QString("Main"), QString("/text")))
                  .arg(QApplication::applicationPid())
                  .arg(sessionName)
                  .arg(rights);

  setWindowTitle(title);

  // Установка внешнего вида приложения
  int style = QString(appsetup.getApplicationParam(
                        QString("Main"),
                        QString("/style"))
                      ).toInt(&ok, 10);

  switch (style) {
  case QPLASTIQUESTYLE:
    QApplication::setStyle( QStyleFactory::create("Fusion") );
    break;
  case QWINDOWSXPSTYLE:
    QApplication::setStyle( QStyleFactory::create("windowsxp") );
    break;
  case QWINDOWSSTYLE:
    QApplication::setStyle( QStyleFactory::create("windows") );
    break;
  case QCDESTYLE:
    QApplication::setStyle( QStyleFactory::create("Fusion") );
    break;
  case QMOTIFSTYLE:
    QApplication::setStyle( QStyleFactory::create("macintosh") );
    break;
  default:
    QApplication::setStyle( QStyleFactory::create("windowsxp") );
    break;
  }

}

/*
 * Деструктор основной формы главного приложения
 */
MainWindow::~MainWindow() {
}

/*
 * Закрытие основного окна приложения
 */
void MainWindow::closeEvent( QCloseEvent *event ) {

  bool isTestStarted = Cve::instance().getParameterValue(QString("testStarted"), false);

  if (isTestStarted) {
    event->ignore();
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"),
                          tr("Идет тест, завершите тест корректно!"));

  } else {
    mdiArea->closeAllSubWindows();
    event->accept();

    QSettings settings(Information::instance().company(), QString("%1_%2").arg(Information::instance().mainTitleApp()).arg(Information::instance().version()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
  }

}


/*
 * Признак того что форма видима и активна
 */
QWidget *MainWindow::isVisibleAndActiveMdiChild() {
  if ( QMdiSubWindow *activeSubWindow = Core::CveGui::instance().mdi()->activeSubWindow() ) {
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
  Core::CveGui::instance().activWindowsListToolBar->clear();

  // Получение списка всех окон из subWindowList
  QList<QMdiSubWindow *> windows = mdiArea->subWindowList();

  Core::CveGui::instance().activWindowsListToolBar->setToolButtonStyle(
        Qt::ToolButtonTextBesideIcon );

  // TODO: при обращении к элементам QList необходима проверка на его пределы
  // Поиск видимы окон и добавление их в панель активных окон
  for ( int i = 0; i < windows.size(); ++i ) {
    if ( (windows.at(i)->isVisible()) || (windows.at(i)->isMinimized()) ) {
      QWidget *child  = qobject_cast<QWidget *>(windows.at(i)->widget());
      // Создание действия
      QAction   *action =
          Core::CveGui::instance().activWindowsListToolBar->addAction(
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
    _documentsApi.append(act);
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

  msg = QString("%1 %2 %3").arg(Information::instance().aboutMessageTop()).arg(Information::instance().version())
                           .arg(Information::instance().aboutMessageBottom());

  QMessageBox::about( NULL,
                      QString("%1 %2").arg(Information::instance().aboutMessageTitle()).arg(Information::instance().version()),
                      msg );
}


