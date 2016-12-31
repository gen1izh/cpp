#include "man.h"

/*
 * Возвращает действие из списка пар (виджет,действие)
 */
QAction *man::getManagerAction_FromWAPair(QString managerName, QString waName) {
  return Core::Plugins::instance().managers().value(managerName)->getWidgetActionList().value(waName).second;
}

/*
 * Возвращает виджет из списка пар (виджет,действие)
 */
QWidget *man::getManagerWidget_FromWAPair(QString managerName, QString waName) {
  return Core::Plugins::instance().managers().value(managerName)->getWidgetActionList().value(waName).first;
}

/*
 * Возвращает дествие из списка действий плагина
 */
QAction *man::getManagerAction_FromActionsList(QString managerName, QString actionName) {
  return Core::Plugins::instance().managers().value(managerName)->getActionList()[actionName];
}

/*
 * Возвращает действие из списка пар (виджет,действие)
 */
QAction *man::getLoggerAction_FromWAPair(QString waName) {
  return Core::Plugins::instance().logger()->getWidgetActionList().value(waName).second;
}

/*
 * Возвращает виджет из списка пар (виджет,действие)
 */
QWidget *man::getLoggerWidget_FromWAPair(QString waName) {
  return Core::Plugins::instance().logger()->getWidgetActionList().value(waName).first;
}

/*
 * Возвращает дествие из списка действий плагина
 */
QAction *man::getLoggerAction_FromActionsList(QString waName) {
  return Core::Plugins::instance().logger()->getActionList().value(waName);
}


