#ifndef CVE_LOGGER_APP_DATA_H
#define CVE_LOGGER_APP_DATA_H

/*!
 * \brief   Менеджер журналирования.
 * \details Журнал должен быть в любом приложении. Менеджер журналирования обеспечивает
 * набор функций, позволяющих работать с различными журналами.
 * Менеджер журналирования реализует интерфейс <i><b>ILoggerManager</b></i>. Для разных приложения будет
 * разный журнал, сделать универсальный, много функциональный невозможно, поэтому
 * <i><b>ILogger</b></i> интерфейс содержит только одну функцию <i><b>log</b></i>. Всю остальную всю остальную
 * нагрузку по журналированию берет на себя разработчик модуля или плагина.
 * Разработчик плагина или модуля будет обращаться к менеджеру журналирования через
 * главный менеджер <i><b>CveManager</b></i> и использовать функцию log, для этого в своем модуле\менеджере
 * разработчик должен позаботиться о создании класс-обертки этой функции, для того
 * чтобы было удобней вести журналирование.
 * Принято 4 типо журналов:
 * <ul>
 *  <li> <i><b>SYSTEM_LOG</b></i> - системный журнал (протоколируются сообщения core)
 *  <li> <i><b>USER_LOG</b></i> - пользовательский журнал (протоколируются сообщения managers, formManager)
 *  <li> <i><b>MODULE_LOG</b></i> - журнал модулей (протоколируются сообщения из модулей)
 *  <li> <i><b>SCRIPT_LOG</b></i> - журнал скриптов (протоколируются сообщения скриптов)
 * </ul>
 * Задача заключалась в том чтобы разделить журналы по сущностям ПО.
 * Каждый журнал протоколирует только свою сущность. Для каждого типа журнала создается свой
 * файл (хранилище данных). Данные сообщений в котором формируются в формате CSV.
 *
 * \note Для некоторого удобства в библиотеке ядра реализован LoggerApi, который
 * позволяет вести журналировани, но эти функции будут актуальны лишь для текущего плагина
 * журналирования.
 *
 * \todo При разработке данного плагина в планах было создать универсальную систему выбора
 * хранилища. Интерфейс хранилища представлен классом ILoggerStorage, который затем
 * переопределяют конкретные хранилища. Необходимо переработать архитектуру плагина в данной части
 * и ввести реализацию паттерна policy для того более гибко выбирать хранилище.
 *
 * \todo При обработке данных(фильтрации) применяются не гибкие методы. К пример сообщения
 * складируются все в один список, затем при при необходимой фильтрации заполняется новый список.
 * Сама реализация алгоритмов фильтрации не гибкая и вероятно с ошибками. Необходимо доделать
 * архитектуру алгоритмов фильтрации, упростить их.
 *
 * \warning Необходимо доработать архитектуру плагина журналирования до того как
 * демонстрировать код сторонним разработчикам.
 *
 */

#include <QDockWidget>

// Подключаемые компоненты
#include <interfaces/iloggermanager.h>
#include <plugins/logger/logger/filestorage.h>
#include <plugins/logger/logger/loggerssettingspage.h>
#include <plugins/logger/logger/logger.h>

#include "loggerexport.h"

#include "logerscriptapi.h"

/*!
 * \brief Класс плагина журналирования
 */
class LOGGER_EXPORT CveLogger : public QObject, public ILoggerPlugin {

  Q_OBJECT

  Q_PLUGIN_METADATA(IID ILoggerPlugin_iid FILE "logger.json")
  Q_INTERFACES(ILoggerPlugin)

  /*!
   * \brief Класс настроек журналов
   */
  LoggersSettingsPage *_settings;

  /*!
   * \brief Действия для открытия просмотрщика отчетов
   */
  QAction *_loggersWatcherAct;

  /*!
   * \brief Указатель на обретку журнала- скриптапи
   */
  LogerScriptApi *_scripts;

  public:

  CveLogger();

    ~CveLogger(){}

    /*!
     * \brief Возвращает указатель на форму настроек
     * \return
     */
    QWidget *getSettingPage() {
      if (_settings == NULL) {
        _settings = new LoggersSettingsPage();
      }
      return _settings;
    }

    /*!
     * \brief Создание виджетов плагина
     */
    void createWidgets();

    /*!
     * \brief
     */
    void createActions(){}

    /*!
     * \brief
     */
    void createConnectors(){}


    /*!
     * \brief Возвращает иконку для настроек
     * \return
     */
    QIcon settingIcon() {
      return QIcon(":/settings/img/log.png");
    }


    /*
                      Функции журналирования для устройств
                                                                        */

    /*!
     * \brief Функция журналирования сообщения
     * \param[in] ptr  - указатель на объект источник сообщения
     * \param[in] txt  - текст сообщения
     * \param[in] type - тип сообщения
     * \param[in] loggertype - тип журнала
     */
    void log(QObject *ptr,
             QString txt,
             MessagesTypes type,
             LoggersTypes loggertype = SYSTEM_LOG);

};

#endif // CVE_LOGGER_APP_DATA_H