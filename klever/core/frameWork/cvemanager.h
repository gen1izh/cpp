#ifndef CVE_MANAGER_H
#define CVE_MANAGER_H

/* Библиотека утилит */
#include <library/utilsLibrary/utilslibrary.h>
#include <library/message/messagelibrary.h>

/* Включения для объектов-оберток модуля скриптов */
#include <managers/logger/logger/logger.h>
#include <managers/logger/logger/loggerssettingspage.h>
//#include <managers/testsequence/cveTestSequences.h>

#include <settings/appsettings.h>

#include <interfaces/iloggermanager.h>
#include <interfaces/ibootmanager.h>
#include <interfaces/moduleinterface.h>

#include <settings/modules/modulesmanager.h>

#include <QFileInfo>

/*!
 * \brief Класс главного менеджера над менеджерами компонентов ядра
 */
class CveManager : public QObject {

  Q_OBJECT

  CveManager() {
    setObjectName(tr("Главный менеджер"));
  }


  CveManager(const CveManager& root);
  CveManager& operator=(const CveManager&);

  /*!
   * \brief  Указатель на объект менеджера журнала
   */
  ILoggerManager    *_iloggermanager;

  /*!
   * \brief Указатель на загрузочный менеджер
   */
  IBootManager      *_ibootmanager;

  /*!
   * \brief Хеш менеджеров
   */
  QHash<QString, ManagerInterface *> _managers;


  public:

   // Чтобы иметь доступ через пространство имен извне класса
   // состояния  в public секции
   enum States {
     SUCCESSFUL,
     BOOT_LOADING_ERROR,
     LOGGER_LOADING_ERROR,
     MANAGERS_LOADING_ERROR,
     NO_MANAGERS_ERROR,
     NO_MAIN_INI_ERROR
   };

    static CveManager& instance();

    /*!
     * \brief Возвращает указатель на объект журнала
     * \return
     */
    ILoggerManager  *logger() const {
      if (_iloggermanager==NULL) {
        //TODO: добавить QMessage сообщение отсутствия журнала
       // Создали системный журнал
      }
      return _iloggermanager;
    }

    /*!
     * \brief Возвращает указатель на объект загрузочного менеджера
     * \return
     */
    IBootManager  *boot() const {
      if (_ibootmanager==NULL) {
        //TODO: добавить QMessage сообщение отсутствия загрузчика
       qDebug().noquote() << "Загрузчик не был корректно подключен!";
      }
      return _ibootmanager;
    }

    /*!
     * \brief Инициализация менеджеров
     * \return Возвращает код ошибки, если 0 - то успешно.
     */
    int loadManagers();

    /*!
     * \brief Возвращает хеш менеджеров
     * \return
     */
    QHash<QString, ManagerInterface *> managers() const {
      if (_managers.isEmpty()) {
        //TODO: добавить QMessage сообщение отсутствия менеджеров
      }
      return _managers;
    }

    /*!
     * \brief Финализация работы главного менеджера
     * \details Удаляет все менеджеры
     */
    void finalize();

    /*!
     * \brief Возвращает признак существования файла main.ini
     * \return
     */
    bool isMainIniExist() {
      QString path = QString("%1\\%2").arg(QDir::currentPath()).arg("main.ini");
      QFileInfo fil(path);
      if (!fil.exists()) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Главный менеджер"),
                               tr("Конфигурационный файл main.ini не найден! "
                                  "Попробуйте запустить конфигуратор и создать main.ini."));
        return false;
      }
      return true;
    }

    /*!
     * \brief isManagerExist
     * \param name
     * \return
     */
    bool isManagerExist(QString name) {
      QHashIterator<QString, ManagerInterface *>  i(_managers);
      while (i.hasNext()) {
        i.next();
        if ( name == i.key() ) {
          return true;
        }
      }
      return false;
    }

    /*!
     * \brief Создание виджетов менеджеров
     */
    void createWidgets();

    /*!
     * \brief Подготовка всех менеджеров
     */
    void createActions();

    /*!
     * \brief Создание коннекторов
     */
    void createConnectors();
};

#endif // CVE_MANAGER_H
