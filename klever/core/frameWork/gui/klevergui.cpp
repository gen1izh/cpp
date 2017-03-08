
// Подключение статус бара главного окна
#include "mainwindow/mainwindow.h"
#include "klevergui.h"

Core::KleverGui::KleverGui()
{
  setObjectName("Графическая среда");
  activWindowsListToolBar = new QToolBar();
  _waitingOperaion = false;
}

/*
 * Инициализация mainwindow и mdiarea
 */
void Core::KleverGui::initializeMainwindowAndMdi()
{
  m_mainwindow  = new MainWindow();
  _mdi  = ((MainWindow *)m_mainwindow)->mdiArea;
}


Core::KleverGui &Core::KleverGui::instance() {
  static KleverGui singleObject;
  return singleObject;
}

int Core::KleverGui::load()
{

    return 0;
}

// Финализация работы ГИП
int Core::KleverGui::finalize()
{
    // Удаление главного окна приложения
    delete m_mainwindow;
    // Зануление указателя на главное окно приложения
    m_mainwindow = NULL;

    return 0;
}

/*
 * Подготовка ГИП
 */
void Core::KleverGui::prepare() {

  Library::LoggerApi::logInfo(this,"Создание действий");
  ((MainWindow *)m_mainwindow)->createActions();

  Library::LoggerApi::logInfo(this,"Создание главного меню приложения");
  ((MainWindow *)m_mainwindow)->createMenu();

  Library::LoggerApi::logInfo(this,"Создание коннекторов");
  ((MainWindow *)m_mainwindow)->createConnectors();

  Library::LoggerApi::logInfo(this,"Создание меню быстрого запуска");
  ((MainWindow *)m_mainwindow)->createToolBars();

  Library::LoggerApi::logInfo(this,"Создание доков");

  ((MainWindow *)m_mainwindow)->createDockWindows();

  // Коннекторы модуля настроек приложения
  connect( ((MainWindow *)m_mainwindow)->appSettingAction(), SIGNAL(triggered()),
           formManager, SLOT(openAppOptionsWindow()) );

  connect( ((MainWindow *)m_mainwindow)->moduleInfoAction(), SIGNAL(triggered()),
           formManager, SLOT(openPluginInfoWindow()) );

}

/*
 * Инициализация плагина форм
 */
void Core::KleverGui::initializeFormManager()
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
QMdiSubWindow *Core::KleverGui::findMdiChild( QString id ) {
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
void Core::KleverGui::restoreDocksPosition() {
  QSettings settings(Information::instance().company(),
                     QString("%1_%2").arg(Information::instance().mainTitleApp())
                     .arg(Information::instance().version()));
  bool res = m_mainwindow->restoreGeometry(settings.value("geometry").toByteArray());
  if (!res) {
    Library::LoggerApi::logError(this,"Восстановление геометрии не выполнено!");
  }

  res = m_mainwindow->restoreState(settings.value("windowState").toByteArray());
  if (!res) {
    Library::LoggerApi::logError(this,"Восстановление состояний доков не выполнено!");
  }
}

/*
 * Обработчик события скрытия формы
 */
bool Core::KleverGui::eventFilter(QObject *obj, QEvent *event) {
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
void Core::KleverGui::showMaximized(){
  m_mainwindow->showMaximized();
  Library::LoggerApi::logInfo(this,"Главное окно приложения максимизировано");
}


/*
 * Сплеш-скрин. Информирование о загрузке модуля.
 */
void Core::KleverGui::splashMessage(QString txt) {

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
void Core::KleverGui::initializeSplashScreen() {

    QPixmap pixmap;

    if(Information::instance().logo() != "default") {
        pixmap.load(QCoreApplication::applicationDirPath() + "/" + Information::instance().logo());
    }
    else {
        pixmap.load(":/images/logo.png");
    }

    _splash = new QSplashScreen();
    _splash->setPixmap(pixmap);
    _splash->show();
    _splash->showMessage(QString("Запуск приложения"));
}

/*
 * Отключение сплеш-скрина
 */
void Core::KleverGui::finishSplashScreen()
{
  _splash->finish(m_mainwindow);
  delete _splash;
}

/*
 * Функция блокирования MainWindow до окончания длительной операции
 */
void Core::KleverGui::startDialog(QString msg)
{
  _procDialog.setDialog(msg);
  _procDialog.start();
  m_mainwindow->setEnabled(false);
  _waitingOperaion = false;
}

/*
 * Функция разблокирования MainWindow после окончания длительной операции
 */
void Core::KleverGui::closeDialog()
{
  _procDialog.finish();
  m_mainwindow->setEnabled(true);
  _waitingOperaion = false;
}


