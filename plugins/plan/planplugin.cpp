#include "planplugin.h"

planPlugin::planPlugin() {
    setName("plan");
    setTextName("%{PluginName}");
    createWidgets();
}

void planPlugin::createWidgets() {

    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new planSettings(NULL);
    }

    // Необходимо добавить остальные виджеты

}

/*
 * Деинициализация элементов
 */
void planPlugin::finalize() {

}


/*
 * Возвращает виджет настроек
 */
QWidget *planPlugin::settingPage() {
    return static_cast<QWidget *>(m_settings);
}

/*
 *  Возвращает иконку для настроек
 */
QIcon planPlugin::settingIcon() {
    return QIcon(":/planplugin/img/plugin.png");
}


