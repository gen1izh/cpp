#ifndef TUBE_MANAGER_H
#define TUBE_MANAGER_H

/*!
 * brief
 * date
 */
class TubeManager;

#include <frameWork/cve.h>
#include "widgets/settings/tubesettingswidget.h"

class TubeManager : public QObject, public ManagerInterface {

  Q_OBJECT

  Q_PLUGIN_METADATA(IID ManagerInterface_iid FILE "tube.json")
  Q_INTERFACES(ManagerInterface)

  /*!
   * brief Виджет настроек
   */
  TubeSettings *_settings;

public:

  TubeManager();

  ~TubeManager() {
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
  void createActions() {}

  /*!
   * \brief Созданией коннекторов
   */
  void createConnectors() {}

  /*!
   * brief Деинициализация элементов менеджера
   */
  void finalize();

public slots:

};


#endif // TUBE_MANAGER_H

