#ifndef cintegration_PLUGIN_H
#define cintegration_PLUGIN_H

#include <frameWork/base.h>
#include "widgets/settings/settingswidget.h"

class cintegrationPlugin;

class cintegrationPlugin : public QObject, public PluginInterface {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "cintegration.json")
    Q_INTERFACES(PluginInterface)


    cintegrationSettings *m_settings;

public:

    cintegrationPlugin();

    ~cintegrationPlugin() {
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


#endif // cintegration_PLUGIN_H
