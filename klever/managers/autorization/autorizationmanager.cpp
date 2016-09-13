#include "autorizationmanager.h"

AutorizationManager::AutorizationManager() {
    initialize(tr("autorization"), tr("Авторизация"));
}

AutorizationManager::~AutorizationManager()
{
    finalize();
}

bool AutorizationManager::execute()
{

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
    // TODO: ...
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

void AutorizationManager::createActions()
{
    // TODO: ...
}

void AutorizationManager::createConnectors()
{
    // TODO: ...
}



