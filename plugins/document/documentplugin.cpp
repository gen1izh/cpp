#include "documentplugin.h"

documentPlugin::documentPlugin() {
    setName("document");
    setTextName("document");
    createWidgets();
}

void documentPlugin::createWidgets() {

    _widgetActionList[tr("(PM)BF_DocumentsForm")].first  = new BF_DocumentsForm();
    _widgetActionList[tr("(PM)BF_DocumentsForm")].second = m_BF_DocumentsForm;

    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new documentSettings(NULL);
    }

    // Необходимо добавить остальные виджеты

}

/*
 * Деинициализация элементов
 */
void documentPlugin::finalize() {

}

/*
 * Возвращает виджет настроек
 */
QWidget *documentPlugin::settingPage() {
    return static_cast<QWidget *>(m_settings);
}

/*
 *  Возвращает иконку для настроек
 */
QIcon documentPlugin::settingIcon() {
    return QIcon(":/documentplugin/img/plugin.png");
}

void documentPlugin::createActions()
{
    m_BF_DocumentsForm = new QAction(QIcon(":/documentplugin/img/plugin.png"),
                                       tr("&Документация"),
                                       this);
}


