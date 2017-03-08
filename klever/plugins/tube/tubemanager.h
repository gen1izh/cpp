#ifndef TUBE_MANAGER_H
#define TUBE_MANAGER_H

/*!
 * brief
 * date
 */
class TubeManager;

#include <frameWork/base.h>
#include "widgets/settings/settingsform.h"

class TubeManager : public QObject, public PluginInterface {

  Q_OBJECT

  Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "tube.json")
  Q_INTERFACES(PluginInterface)

  /*!
   * brief Виджет настроек
   */
  SettingsForm *m_settings;

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
   * brief Возвращает виджет настроек плагина
   * return
   */
  QWidget *settingPage();

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
   * \brief Информация о плагине
   */
  QString information();

  /*!
   * brief Деинициализация элементов плагина
   */
  void finalize();

public slots:

};


#endif // TUBE_MANAGER_H

