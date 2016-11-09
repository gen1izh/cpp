#include "formsManager.h"

#include <frameWork/gui/klevergui.h>
#include <frameWork/managers.h>


/*
 * Конструктор менеджера форм
 */
FormsManager::FormsManager() {
  setObjectName(tr("Менеджер форм"));  // Установка имени модуля
  createActions();                     // Создание действий
  createConnections();                 // Создание соединений
}

