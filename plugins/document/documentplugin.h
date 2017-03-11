#ifndef document_PLUGIN_H
#define document_PLUGIN_H

#include <frameWork/base.h>
#include "widgets/settings/settingswidget.h"
#include "widgets/document/bf_documentsform.h"


class documentPlugin;

class documentPlugin : public QObject, public PluginInterface {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "document.json")
    Q_INTERFACES(PluginInterface)


    documentSettings *m_settings = NULL;
    QAction *m_BF_DocumentsForm;

     QAction *m_TextEditorOpen;

public:

    documentPlugin();

    ~documentPlugin() {
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


#endif // document_PLUGIN_H
