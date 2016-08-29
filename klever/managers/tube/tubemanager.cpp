#include "tubemanager.h"

TubeManager::TubeManager() {
  setName("/tube");         // Установка имени модуля (внутреннее)
  setTextName("Труба");    // Установка имени модуля (внешнее)
  checkManagerState();            // Проверка состояния менеджера (вкл. или выкл.)
  createWidgets();
  _settings = NULL;
}

/*
 * Создание виджетов модуля
 */
void TubeManager::createWidgets() {

  // Необходимо добавить остальные виджеты

  // Создание виджета настроек
  if (_settings==NULL) {
    _settings = new TubeSettings(NULL);
  }

}

/*
 * Деинициализация элементов менеджера
 */
void TubeManager::finalize() {

}


/*
 * Возвращает виджет настроек менеджера
 */
QWidget *TubeManager::getSettingPage() {
  QWidget* wgt=static_cast<QWidget *>(_settings);
  return wgt;
}

/*
 *  Возвращает иконку для настроек
 */
QIcon TubeManager::settingIcon() {
  return QIcon(":/tubemanager/img/manager.png");
}



