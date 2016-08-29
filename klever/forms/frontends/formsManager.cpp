#include "formsManager.h"

#include <frameWork/gui/cvegui.h>
#include <frameWork/CveManager.h>


/*
 * Конструктор менеджера форм
 */
FormsManager::FormsManager() {
  setObjectName(tr("Менеджер форм"));  // Установка имени модуля
  createActions();                     // Создание действий
  createConnections();                 // Создание соединений
}

