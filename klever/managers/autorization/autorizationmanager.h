#ifndef autorization_MANAGER_H
#define autorization_MANAGER_H

#include "widgets/settings/autorizationsettingswidget.h"

/*!
 * brief   %{ModuleName} * details %{ModuleDescription} * author  %{ModuleAuthor}, gen.izh@yandex.ru
 * date
 */
class autorizationManager;

#include <frameWork/cve.h>

class autorizationManager : public QObject, public ManagerInterface {

  Q_OBJECT

  Q_PLUGIN_METADATA(IID ManagerInterface_iid FILE "autorization.json")
  Q_INTERFACES(ManagerInterface)

  /*!
   * brief Виджет настроек
   */
  autorizationSettings *_settings = NULL;

public:

  autorizationManager();

  ~autorizationManager() {
    finalize();
  }

  /*!
   * brief Создание виджетов модуля
   */
  void createWidgets();

  /*!
   * brief Возвращает виджет настроек менеджера
   * return
   */
  QWidget *getSettingPage();

  /*!
   * brief Возвращает иконку для настроек
   * return
   */
  QIcon settingIcon();

  /*!
   * \brief Создание действий
   */
  virtual void createActions() {}

  /*!
   * \brief Созданией коннекторов
   */
  virtual void createConnectors() {}


  /*!
   * brief Деинициализация элементов менеджера
   */
  void finalize();

public slots:

};


#endif // autorization_MANAGER_H

