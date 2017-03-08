#include "cintegrationplugin.h"

cintegrationPlugin::cintegrationPlugin() {
    setName("cintegration");
    setTextName("cintegration");
    createWidgets();
}

void cintegrationPlugin::createWidgets() {

    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new cintegrationSettings(NULL);
    }

    // Необходимо добавить остальные виджеты

}

/*
 * Деинициализация элементов
 */
void cintegrationPlugin::finalize() {

}


/*
 * Возвращает виджет настроек
 */
QWidget *cintegrationPlugin::settingPage() {
    return static_cast<QWidget *>(m_settings);
}

/*
 *  Возвращает иконку для настроек
 */
QIcon cintegrationPlugin::settingIcon() {
    return QIcon(":/cintegrationplugin/img/plugin.png");
}


