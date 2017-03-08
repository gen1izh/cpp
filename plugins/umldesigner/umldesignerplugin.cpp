#include "umldesignerplugin.h"

umldesignerPlugin::umldesignerPlugin() {
    setName("umldesigner");
    setTextName("%{PluginName}");
    createWidgets();
}

void umldesignerPlugin::createWidgets() {

    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new umldesignerSettings(NULL);
    }

    // Необходимо добавить остальные виджеты

}

/*
 * Деинициализация элементов
 */
void umldesignerPlugin::finalize() {

}


/*
 * Возвращает виджет настроек
 */
QWidget *umldesignerPlugin::settingPage() {
    return static_cast<QWidget *>(m_settings);
}

/*
 *  Возвращает иконку для настроек
 */
QIcon umldesignerPlugin::settingIcon() {
    return QIcon(":/umldesignerplugin/img/plugin.png");
}


