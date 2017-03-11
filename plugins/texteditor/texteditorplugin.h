#ifndef texteditor_PLUGIN_H
#define texteditor_PLUGIN_H

#include <frameWork/base.h>
#include "widgets/settings/settingswidget.h"
#include "widgets/texteditor/editorform.h"

class texteditorPlugin;

class texteditorPlugin : public QObject, public PluginInterface {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "texteditor.json")
    Q_INTERFACES(PluginInterface)

    QAction *m_TextEditor;
    texteditorSettings *m_settings = NULL;

public:

    texteditorPlugin();

    ~texteditorPlugin() {
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
    QString information(){ return QString(""); }

    /*!
   * brief Деинициализация элементов
   */
    void finalize();

public slots:

};


#endif // texteditor_PLUGIN_H
