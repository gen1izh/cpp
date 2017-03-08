#ifndef architect_PLUGIN_H
#define architect_PLUGIN_H

#include <frameWork/base.h>
#include "widgets/settings/settingswidget.h"
#include "widgets/architect/bf_architectform.h"

class architectPlugin;

class architectPlugin : public QObject, public PluginInterface {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "architect.json")
    Q_INTERFACES(PluginInterface)

    QAction *m_BF_ArchitectForm;

    architectSettings *m_settings= NULL;

public:

    architectPlugin();

    ~architectPlugin() {
        finalize();
    }

    /*!
   * brief Создание виджетов
   */
    void createWidgets();

    /*!
   * brief Возвращает виджет настроек
   * return
   */
    QWidget *settingPage();

    /*!
   * brief Возвращает иконку для настроек
   * return
   */
    QIcon settingIcon();

    /*!
   * brief Создание действий
   */
    void createActions();

    /*!
   * brief Созданией коннекторов
   */
    void createConnectors() {}

    /*!
   * brief Информация о плагине
   */
    QString information() { return QString(""); }

    /*!
   * brief Деинициализация элементов
   */
    void finalize();

public slots:

};


#endif // architect_PLUGIN_H
