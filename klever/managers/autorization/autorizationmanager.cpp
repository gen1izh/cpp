#include "autorizationmanager.h"

autorizationManager::autorizationManager() {
  setName("autorization");         // Установка имени модуля (внутреннее)
  setTextName("Авторизация");  // Установка имени модуля (внешнее)
  setOnOrOff(true);
  createWidgets();


}

/*
 * Создание виджетов модуля
 */
void autorizationManager::createWidgets() {

  // Необходимо добавить остальные виджеты

  // Создание виджета настроек
  if (_settings==NULL) {
    _settings = new autorizationSettings(NULL);
  }

}

/*
 * Деинициализация элементов менеджера
 */
void autorizationManager::finalize() {

}


/*
 * Возвращает виджет настроек менеджера
 */
QWidget *autorizationManager::getSettingPage() {
  QWidget* wgt=static_cast<QWidget *>(_settings);
  return wgt;
}

/*
 *  Возвращает иконку для настроек
 */
QIcon autorizationManager::settingIcon() {
  return QIcon(":/autorizationmanager/img/manager.png");
}



