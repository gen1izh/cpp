#ifndef taskmaster_PLUGIN_H
#define taskmaster_PLUGIN_H

#include <frameWork/base.h>
#include "widgets/settings/settingswidget.h"

class taskmasterPlugin;

class taskmasterPlugin : public QObject, public PluginInterface {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "taskmaster.json")
    Q_INTERFACES(PluginInterface)


    taskmasterSettings *m_settings;

public:

    taskmasterPlugin();

    ~taskmasterPlugin() {
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
    void createActions(){}

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


#endif // taskmaster_PLUGIN_H
