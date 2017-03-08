#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

/*!
 * brief
 * date
 */
class ProjectManager;

#include <frameWork/base.h>
#include "widgets/settings/settingsform.h"

class ProjectManager : public QObject, public PluginInterface {

  Q_OBJECT

  Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "project_manager.json")
  Q_INTERFACES(PluginInterface)

  /*!
   * brief Виджет настроек
   */
  SettingsForm *m_settings;

//  QAction *m_BF_AnalizeForm;
//  QAction *m_BF_ArchitectForm;
//  QAction *m_BF_DeployBuildForm;
//  QAction *m_BF_DocumentsForm;

public:

  ProjectManager();

  ~ProjectManager() {
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
  void createActions();

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


#endif // PROJECT_MANAGER_H

