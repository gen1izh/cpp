#include "tubemanager.h"

TubeManager::TubeManager() {
  setName("tube");         // Установка имени модуля (внутреннее)
  setTextName("Труба");    // Установка имени модуля (внешнее)
  checkManagerState();            // Проверка состояния плагина (вкл. или выкл.)
  createWidgets();
  m_settings = NULL;
}

/*
 * Создание виджетов модуля
 */
void TubeManager::createWidgets() {

  // Необходимо добавить остальные виджеты

  // Создание виджета настроек
  if (m_settings==NULL) {
    m_settings = new SettingsForm(NULL);
  }

}

/*
 * Деинициализация элементов плагина
 */
void TubeManager::finalize() {

}


/*
 * Возвращает виджет настроек плагина
 */
QWidget *TubeManager::settingPage() {
  QWidget* wgt=static_cast<QWidget *>(m_settings);
  return wgt;
}

/*
 *  Возвращает иконку для настроек
 */
QIcon TubeManager::settingIcon() {
    return QIcon(":/tubemanager/img/manager.png");
}

QString TubeManager::information()
{
    QString msg = "truba";

    return msg;
}



