#include "taskmasterplugin.h"

taskmasterPlugin::taskmasterPlugin() {
    setName("taskmaster");
    setTextName("%{PluginName}");
    createWidgets();
}

void taskmasterPlugin::createWidgets() {

    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new taskmasterSettings(NULL);
    }

    // Необходимо добавить остальные виджеты

}

/*
 * Деинициализация элементов
 */
void taskmasterPlugin::finalize() {

}


/*
 * Возвращает виджет настроек
 */
QWidget *taskmasterPlugin::settingPage() {
    return static_cast<QWidget *>(m_settings);
}

/*
 *  Возвращает иконку для настроек
 */
QIcon taskmasterPlugin::settingIcon() {
    return QIcon(":/taskmasterplugin/img/plugin.png");
}


