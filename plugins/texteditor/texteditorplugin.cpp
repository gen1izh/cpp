#include "texteditorplugin.h"

texteditorPlugin::texteditorPlugin() {
    setName("texteditor");
    setTextName("%{PluginName}");
    createWidgets();
}

void texteditorPlugin::createWidgets() {

    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new texteditorSettings(NULL);
    }

    // Необходимо добавить остальные виджеты

}

/*
 * Деинициализация элементов
 */
void texteditorPlugin::finalize() {

}


/*
 * Возвращает виджет настроек
 */
QWidget *texteditorPlugin::settingPage() {
    return static_cast<QWidget *>(m_settings);
}

/*
 *  Возвращает иконку для настроек
 */
QIcon texteditorPlugin::settingIcon() {
    return QIcon(":/texteditorplugin/img/plugin.png");
}


