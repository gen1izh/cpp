#include "autorizationmanager.h"

AutorizationManager::AutorizationManager() {
    setName("autorization");     // Установка имени модуля (внутреннее)
    setTextName("Авторизация");  // Установка имени модуля (внешнее)
    setOnOrOff(true);
    createWidgets();


}

/*
 * Создание виджетов модуля
 */
void AutorizationManager::createWidgets() {

    // Необходимо добавить остальные виджеты

    // Создание виджета настроек
    if (_settings==NULL) {
        _settings = new autorizationSettings(NULL);
    }

}

/*
 * Деинициализация элементов менеджера
 */
void AutorizationManager::finalize() {

}


/*
 * Возвращает виджет настроек менеджера
 */
QWidget *AutorizationManager::getSettingPage() {
    QWidget* wgt=static_cast<QWidget *>(_settings);
    return wgt;
}

/*
 *  Возвращает иконку для настроек
 */
QIcon AutorizationManager::settingIcon() {
    return QIcon(":/autorizationmanager/img/manager.png");
}



