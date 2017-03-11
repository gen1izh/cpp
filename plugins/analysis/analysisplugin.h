#ifndef analysis_PLUGIN_H
#define analysis_PLUGIN_H

#include <frameWork/base.h>
#include "widgets/settings/settingswidget.h"
#include "widgets/analysis/bf_analizeform.h"

class analysisPlugin;

class analysisPlugin : public QObject, public PluginInterface {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "analysis.json")
    Q_INTERFACES(PluginInterface)

    analysisSettings *m_settings = NULL;

    QAction *m_BF_AnalizeForm;

    QAction *m_TextEditorOpen;

public:

    analysisPlugin();

    ~analysisPlugin() {
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
    void createConnectors();

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


#endif // analysis_PLUGIN_H
