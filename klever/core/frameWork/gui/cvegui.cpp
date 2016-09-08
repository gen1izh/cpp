
// Подключение статус бара главного окна
#include "mainwindow/mainwindow.h"
#include "cvegui.h"

/*
 * Обращение к синглтону cvegui
 */
Core::CveGui::CveGui()
{
  setObjectName("Графическая среда");
  activWindowsListToolBar = new QToolBar();
  _waitingOperaion = false;
}

/*
 * Инициализация mainwindow и mdiarea
 */
void Core::CveGui::initializeMainwindowAndMdi()
{
  _mainwindow  = new MainWindow();
  _mdi  = ((MainWindow *)_mainwindow)->mdiArea;
}


Core::CveGui &Core::CveGui::instance() {
  static CveGui singleObject;
  return singleObject;
}

int Core::CveGui::load()
{

    return 0;
}

// Финализация работы ГИП
int Core::CveGui::finalize()
{
    // Удаление главного окна приложения
    delete _mainwindow;
    // Зануление указателя на главное окно приложения
    _mainwindow = NULL;

    return 0;
}

/*
 * Подготовка ГИП
 */
void Core::CveGui::prepare() {

  Library::Logger::logInfo(this,"Создание действий");
  ((MainWindow *)_mainwindow)->createActions();

  Library::Logger::logInfo(this,"Создание главного меню приложения");
  ((MainWindow *)_mainwindow)->createMenus();

  Library::Logger::logInfo(this,"Создание коннекторов");
  ((MainWindow *)_mainwindow)->createConnectors();

  Library::Logger::logInfo(this,"Создание меню быстрого запуска");
  ((MainWindow *)_mainwindow)->createToolBars();

  Library::Logger::logInfo(this,"Создание доков");
  ((MainWindow *)_mainwindow)->createDockWindows();

  // Коннекторы модуля настроек приложения
  connect( ((MainWindow *)_mainwindow)->appSettingAction(), SIGNAL(triggered()),
           formManager, SLOT(openAppOptionsWindow()) );

  connect( ((MainWindow *)_mainwindow)->moduleInfoAction(), SIGNAL(triggered()),
           formManager, SLOT(openModuleInfoWindow()) );

}

/*
 * Инициализация менеджера форм
 */
void Core::CveGui::initializeFormManager()
{

  QPluginLoader loader("formsManager");
  QObject *pluginInstance = loader.instance();

  if (pluginInstance) {
    formManager = qobject_cast<IFormManager *>(pluginInstance);
  }
  else {
    qDebug().noquote() << "formsManager:" << loader.errorString();
  }
  qDebug().noquote() << "formManager =" << formManager;
}


/*
 * Поиск формы по идентификатору
 */
QMdiSubWindow *Core::CveGui::findMdiChild( QString id ) {
  foreach ( QMdiSubWindow *window, mdi()->subWindowList() ) {
    QWidget *mdiChild = qobject_cast<QWidget *>(window->widget());
    if ( mdiChild->objectName() == id ) {
      return window;
    }
  }
  return 0;
}

/*
 * Восстановить позиции доков
 */
void Core::CveGui::restoreDocksPosition() {
  QSettings settings(Information::instance().company(), QString("%1_%2").arg(Information::instance().mainTitleApp()).arg(Information::instance().version()));
  bool res = _mainwindow->restoreGeometry(settings.value("geometry").toByteArray());
  if (!res) {
    Library::Logger::logError(this,"Восстановление геометрии не выполнено!");
  }

  res = _mainwindow->restoreState(settings.value("windowState").toByteArray());
  if (!res) {
    Library::Logger::logError(this,"Восстановление состояний доков не выполнено!");
  }
}

/*
 * Обработчик события скрытия формы
 */
bool Core::CveGui::eventFilter(QObject *obj, QEvent *event) {
  QMdiSubWindow *window = qobject_cast<QMdiSubWindow*>(obj);
  if (window) {
    if (event->type() == QEvent::WindowStateChange) {
      if (window->isMinimized()){
        window->overrideWindowFlags(window->windowFlags() | Qt::FramelessWindowHint);
      } else {
        window->overrideWindowFlags(window->windowFlags() & ~Qt::FramelessWindowHint);
      }
    }
    return false;
  }

  return QObject::eventFilter(obj, event);
}

/*
 * При открытии окно будет максимального размера
 */
void Core::CveGui::showMaximized(){
  _mainwindow->showMaximized();
  Library::Logger::logInfo(this,"Главное окно приложения максимизировано");
}


/*
 * Сплеш-скрин. Информирование о загрузке модуля.
 */
void Core::CveGui::splashMessage(QString txt) {

  QTime time;
  time.start();

  for ( int i = 0; i < 10;  ) {
    if ( time.elapsed() > 10 ) {
      time.start();
      ++i;
    }
    _splash->showMessage( txt + QString::number(i) + "%",
                          Qt::AlignHCenter | Qt::AlignBottom,
                          Qt::black );
  }
}

/*
 * Инициализация сплеш скрина
 */
void Core::CveGui::initializeSplashScreen() {
  QPixmap pixmap(":/images/logo.png");
  _splash = new QSplashScreen();
  _splash->setPixmap(pixmap);
  _splash->show();
  _splash->showMessage(QString("Запуск приложения"));
}

/*
 * Отключение сплеш-скрина
 */
void Core::CveGui::finishSplashScreen()
{
  _splash->finish(_mainwindow);
  delete _splash;
}

/*
 * Функция блокирования MainWindow до окончания длительной операции
 */
void Core::CveGui::startDialog(QString msg)
{
  _procDialog.setDialog(msg);
  _procDialog.start();
  _mainwindow->setEnabled(false);
  _waitingOperaion = false;
}

/*
 * Функция разблокирования MainWindow после окончания длительной операции
 */
void Core::CveGui::closeDialog()
{
  _procDialog.finish();
  _mainwindow->setEnabled(true);
  _waitingOperaion = false;
}


