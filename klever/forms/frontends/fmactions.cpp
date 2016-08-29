#include "formsManager.h"

/*
 * Создание действий модулей
 */
void FormsManager::createModulesActions() {
  /*******************************************************************************
   *                  Модуль источника питания
   *******************************************************************************/
  _controlAction = new QAction(
        QIcon(":/control/img/control.png"),
        tr("Управление"), this );
}

/*
 * Создание действий менеджеров
 */
void FormsManager::createManagersActions() {

}


/*
 * Создание действий
 */
void FormsManager::createActions() {
  createModulesActions();
  createManagersActions();
}
