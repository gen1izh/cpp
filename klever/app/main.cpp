#include <QDebug>
#include <QPixmap>
#include <QSplashScreen>
#include <QtWidgets>
#include <core/frameWork/information.h>

// Подключение основного класс приложения MainWindow
#include <core/frameWork/gui/mainwindow/mainwindow.h>

#include <library/singleApplication/singleapplication.h>

/*
 * Инициализация пути к плагинам приложения
 */
QString initPluginsPath() {
  // Устанавливает абсолютный адрес до каталога
  QDir pluginsDir(QCoreApplication::applicationDirPath());

#if defined(Q_OS_MAC)
  if (pluginsDir.dirName() == "MacOS") {
      pluginsDir.cdUp();
      pluginsDir.cdUp();
      pluginsDir.cdUp();
  }
#endif
  // Переход на каталог plugins
  pluginsDir.cd("modules");

  // Получение абсолютного пути до плагинов
  QString pluginsPath = pluginsDir.absolutePath();
  // Установка пути до плагинов
  QCoreApplication::addLibraryPath(pluginsPath);
  // Вывод в консоль путь до плагинов
  qDebug() << "Library paths:" << QCoreApplication::libraryPaths();

  return pluginsPath;
}


/*
 * Тело основной функции программы.
 */
int main(int argc, char *argv[]) {

  // Инициализация класса приложения
  SingleApplication a(argc, argv);

  // Подключение ресурсов приложения
  Q_INIT_RESOURCE(framework_resources);
  Q_INIT_RESOURCE(cvesettingsmanager_resources);
  Q_INIT_RESOURCE(lamplib_resources);


  // Настройка шаблона сообщения выводимого в консоль
  qSetMessagePattern(
        "%{if-debug}[D]%{endif}%{if-warning}[W]%{endif}%{if-critical}[C]"
        "%{endif}%{if-fatal}[F]%{endif} [%{time hh:mm:ss}]%{if-category} "
        "[%{category}]%{endif} [%{file} : %{line}]   *** %{message} ***" );

  // Настройка кодировки приложения
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

  Information::instance();

  Information::instance().readApplicationInformation();

  // Инициализация путей к плагинам приложения
  initPluginsPath();

  // Инициализация ядра
  Cve::instance();

  // Инстанцирование главного менеджера
  CveManager::instance();

  // Инициализация менеджера ГИП
  CveGui::instance();

  QObject::connect(&CveGui::instance(), SIGNAL(blockMainWindowByDialogSignal(QString)),
                   &CveGui::instance(), SLOT(startDialog(QString)));

  QObject::connect(&CveGui::instance(), SIGNAL(unblockMainWindowByDialogSignal()),
                   &CveGui::instance(), SLOT(closeDialog()));

  // Инициализация сплеш-скрина
  CveGui::instance().initializeSplashScreen();

  // Загрузка менеджеров
  // Подразумевается, что после этой операции будет подгружен и boot и logger
  // менеджеры
  int result = CveManager::instance().loadManagers();

  // Если файла main.ini нет, то смысла продолжать исполнения программы - нет.
  // В этом случае пользователь должен запустить конфигуратор.
  if (result==CveManager::NO_MAIN_INI_ERROR) {
    return -1;
  }

  // Запуск кода загрузчика
  if (!CveManager::instance().boot()->execute()) {
    // Удаление всех менеджеров приложения и модулей устройств
    Cve::instance().finalize();
    // Финализация работы ГИП
    CveGui::instance().finalize();
    return -1;
  }

  // Создание действий
  CveManager::instance().createActions();
  // Создание виджетов
  CveManager::instance().createWidgets();
  // Создание коннекторов
  CveManager::instance().createConnectors();

  // Инициализация ГИП
  CveGui::instance();

  // Инициализация mainwindow и mdi
  CveGui::instance().initializeMainwindowAndMdi();

  // Инициализация менеджера модулей
  ModulesManager::instance();

  // Чтение каталога с модулями
  ModulesManager::instance().readModulesPathAndInitialize();

  // Обновление информации о модулях
  ModulesManager::instance().updateModulesList();

  // Инициализация менеджера форм.
  // INFO: Инициализация должна происходить после загрузки всех модулей.
  CveGui::instance().initializeFormManager();

  // Подготовка ГИП
  CveGui::instance().prepare();

  // Инициализация настроек
  Cve::instance().initializeSettings();

  // Журнал готов к работе
  Cve::instance().setParameterValue(QString("loggerReady"),true);

  // Отложенный запуск модулей
  Cve::instance().startModulesBy100ms();

  // При открытии окно будет максимального размера
  CveGui::instance().showMaximized();

  // Отключение сплеш-скрина
  CveGui::instance().finishSplashScreen();

  // Восстановление позиции доков
  CveGui::instance().restoreDocksPosition();

  // Запустить приложение
  int retVal = a.exec();

  // Журнал готов к работе
  Cve::instance().setParameterValue(QString("loggerReady"), false);

  Cve::instance().finalize();
  // Финализация работы ГИП
  CveGui::instance().finalize();

  // Возвращение результата исполнеиня приложения
  return retVal;
}
