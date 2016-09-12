#ifndef MANAGER_INTERFACE
#define MANAGER_INTERFACE

#include <library/setupApi/main.h>
#include <QMenu>
#include <QToolBar>
#include <QMenuBar>
#include <QDebug>

/*!
 * \brief Интерфейс менеджеров приложения
 */
class ManagerInterface {

  /*!
   * \brief Признак активности менеджера
   */
  bool     m_isOn;

  /*!
   * \brief Признак неактивности менеджера
   */
  bool     m_isDisable;

  /*!
   * \brief Название менеджера
   */
  QString  m_name;

  /*!
   * \brief Название менеджера
   */
  QString  m_textname;

  protected:

    /*!
     * \brief Действия менеджера
     * При вызове действия происходит какое-то событие, без открытия окна
     */
    QHash<QString, QAction*> actionList;


    /*!
     * \brief Хеш пар виджет-действие
     * При вызове действия открывается окно в контексте mdi пространства
     */
    QHash<QString, QPair<QWidget*, QAction*> > widgetActionList;

  public:

    ManagerInterface(){}

    virtual ~ManagerInterface(){}

    /*!
     * \brief Устанавливает название для менеджера
     * \param[in] name - название менеджера
     */
    virtual void setName(QString name) { m_name = name; }

    /*!
     * \brief Возвращает название менеджера
     */
    virtual QString name() { return m_name; }


    /*!
     * \brief Устанавливает текстовое название для менеджера
     * \param[in] name - название менеджера
     */
    virtual void setTextName(QString name) { m_textname = name; }

    /*!
     * \brief Возвращает текстовое название менеджера
     */
    virtual QString textName() { return m_textname; }

    /*!
     * \brief Иконка для окна настроек
     * \return возвращает иконку
     */
    virtual QIcon settingIcon() = 0;

    /*!
     * \brief Проверка того факта, что менеджер включен
     * \return
     */
    bool isOn() {
      return m_isOn;
    }

    /*!
     * \brief Проверка того факта, что менеджер будет доступен
     * То есть если менеджер _isDisable = true, то это означает, то что
     * все элементы управления этого менеджера будут неактивны.
     * \return
     */
    bool isDisable() {
      return m_isDisable;
    }

    /*!
     * \brief Функция отключает менеджер или включает его
     * \return
     */
    void setOnOrOff(bool flag) {
      m_isOn = flag;
    }

    /*!
     * \brief Проверка состояния менеджера
     * Если в файле конфигурации менеджера нет, то по умолчанию он
     * считается отключенным
     */
    virtual void checkManagerState() {
      // По умолчанию отключаем менеджер
      setOnOrOff(false);

      // Проверяем включен ли модуль. Чтение настроек.
      MainSetupApi  mainsetup;
      // Проверить состояние менеджера, отключить по-умолчанию.
      mainsetup.checkMainParam(QString("managers"), m_name, QString("off"));
      QString value = mainsetup.getMainParam(QString("managers"), m_name);
      if ( value == "on" ) {
        setOnOrOff(true);
      }
      else {
        setOnOrOff(false);
      }
    }

    /*!
     * \brief Возвращает указатель на форму настроек
     * \return
     */
    virtual QWidget *getSettingPage() = 0;

    /*!
     * \brief Возвращает хеш пар виджет-действие
     */
    virtual QHash<QString, QPair<QWidget*, QAction*> > getWidgetActionList() {
      return widgetActionList;
    }
    /*!
     * \brief Возвращает действия менеджера
     */
    virtual QHash<QString, QAction*> getActionList() {
      return actionList;
    }

    /*!
     * \brief Создание действий
     */
    virtual void createActions() = 0;

    /*!
     * \brief Созданией коннекторов
     */
    virtual void createConnectors() = 0;

    /*!
     * \brief Создание виджетов
     */
    virtual void createWidgets() = 0;
};


// TODO: Расписать зачем это
#define ManagerInterface_iid "ru.irz.cve_software.ManagerInterface"
// Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
Q_DECLARE_INTERFACE(ManagerInterface, ManagerInterface_iid)

#endif // MANAGER_INTERFACE


