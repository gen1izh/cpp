#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

/*!
 * \brief   Менеджер сессий.
 * \details При открытии ПО открывается окно менеджера сессий.
 *          Менеджер сессий содержит список режимов работы с ПО КПА.
 *          Данный менеджер определяет права доступа к компонентам системы.
 *          Например, одному оператору ПО КПА нужно только производить тестирование,
 *          то есть запускать тестовые последовательности. Другому оператору
 *          нужно иметь возможность редактировать и запускать тестовые
 *          последовательности. Соответственно существует 3 категории пользователей:
 *          Разработчик, Регулировщик, Приемщик. На каждую сессию создаются свои
 *          журналы, настройки, отчеты исполнения тестовых последовательностей
 *          и т.д.
 * \date    2015
 */
class SessionManager;

// Подключение библиотек Qt к проекту
#include <QDebug>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QSqlTableModel>
#include <QTableWidgetItem>
#include <QtSql>


#include "widgets/sessionpropertydialog.h"
#include "widgets/sessionstable.h"
#include "widgets/sessioninfodialog.h"



// Подключение интерфейса менеджера
#include <interfaces/ibootmanager.h>

// Подключение функций работы с настройками
#include <library/setupApi/main.h>
#include <library/setupApi/sessions.h>
#include <library/emptypage/emptypage.h>

#include "sessionmanagersettings.h"

#include <frameWork/cve.h>

// FIXME: Зачем засорять глобальное пространство? Вместо директив using следует использовать объявления using.
using namespace SessionViewNamespace;

/*!
 *  \brief Класс менеджера сессий
 *  \details   При открытии ПО открывается окно менеджера сессий.
 *            Менеджер сессий содержит список сессий работы с бортовой машиной.
 *            Служит для разграничения возможностей между разными людьми.
 *            Например, одному оператору ПК нужно только производить тестирование,
 *            то есть запускать тестовые последовательности. Другому оператору
 *            нужно иметь возможность редактировать и запускать тестовые
 *            последовательности. На каждую сессию будут свои журналы, настройки,
 *            отчеты исполнения тестовых последовательностей и т.д.
 *  \image latex session_manager.png "Окно менеджера сессий" width=10cm
 *
 * Окно менеджера сессий состоит из двух состоявляющих:
 * \li таблицы сессий;
 * \li элементов управления;
 *
 *  Таблица сессий содержит список сессий, запись в нее производится при запуске приложения.
 *  Элементы управления позволяют добавлять новую сессию, удалять сессию\сессии,
 *  соединяться с определенной сессией.
 */
class SessionManager : public QObject, public IBootManager
{

  Q_OBJECT

  Q_PLUGIN_METADATA(IID IBootManager_iid FILE "boot.json")
  Q_INTERFACES(IBootManager)

  /*!
   * \brief Проверка существования каталога sessions и ini файла
   * \details Перед работой с файлом сессий, необходимо проверить его существование
   * и если он не существует, то создать.
   */
  void checkSessionContent();

  /*!
   * \brief Виджет настроек сессий
   */
  SessionManagerSettings *_setting;

  /*!
   * \brief Диалоговое окно сессий
   */
  SessionsTable _sessionsDialog;

  /*!
   * \brief Диалоговое окно информации сессий
   */
  SessionInfoDialog _sessionInformationDialog;

  /*!
   * \brief Установка прав доступа на роли
   */
  void setRights();

public:

  /*!
   * \brief Конструктор менеджера сессий
   */
  SessionManager() {
    Q_INIT_RESOURCE(sessionmanager_resources);
    setName(QString("/boot"));
    setTextName(tr("Сессии"));

    // Зануление указателя на виджет сессий
    _setting = NULL;

    // Проверка состояния менеджера
    checkManagerState();

  }

  ~SessionManager() {
    finalize();
  }

  /*!
   * \brief Запуск кода загрузчика
   * \return
   */
  bool execute();

  /*!
   * \brief Проверка наличия сессий по-умолчанию
   */
  void checkDefaultSessions();

  /*!
   * \brief Создание виджетов модуля
   */
  void createWidgets(){
    if (_setting==NULL) {
      _setting = new SessionManagerSettings(NULL);
    }
  }

  void createActions(){}

  void createConnectors(){
  }

  /*!
   * \brief Проверка состояния права данной роли
   * \param r
   * \return
   */
  bool hasRightUser(int r) {
    return hasRight(Cve::instance().getParameterValue(QString("/rights"),QString("none")),
                    static_cast<Right>(r));
  }

  /*!
   * \brief
   * \return
   */
  QWidget *getSettingPage() {
    QWidget* wgt=static_cast<QWidget *>(_setting);
    return wgt;
  }

  /*!
   * \brief Возвращает иконку для настроек
   * \return
   */
  QIcon settingIcon() {
    return QIcon(":/sessionmanager/img/settings/sessions.png");
  }

  /*!
   * \brief Деинициализация элементов менеджера сессии
   */
  void finalize();

  /*!
   * \brief Функция переключения на текущую сессию.
   * \details Используется при запуске приложения
   */
  void switchToCurrentSession();

  /*!
   * \brief Запуск диалогового окна.
   * \details производит запуск диалогового окна менеджера сессий для
   * интерактивного взаимодействия с пользователем ПО
   */
  bool showSessions();


  public slots:


};


#endif // SESSIONMANAGER_H
