#ifndef umldesigner_PLUGIN_H
#define umldesigner_PLUGIN_H

#include <frameWork/base.h>
#include "widgets/settings/settingswidget.h"

class umldesignerPlugin;

class umldesignerPlugin : public QObject, public PluginInterface {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "umldesigner.json")
    Q_INTERFACES(PluginInterface)


    umldesignerSettings *m_settings;

public:

    umldesignerPlugin();

    ~umldesignerPlugin() {
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


#endif // umldesigner_PLUGIN_H
