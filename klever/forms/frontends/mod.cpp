#include "mod.h"

/*
 *  Возвращает действие из списка пар (виджет,действие)
 */
QAction *mod::getModuleAction_FromWAPair(QString moduleName, QString waName, int id) {
  return ModulesManager::instance().modules()[moduleName].at(id).i->getWidgetActionList()[waName].second;
}

/*
 * Возвращает виджет из списка пар (виджет,действие)
 */
QWidget *mod::getModuleWidget_FromWAPair(QString moduleName, QString waName, int id) {
  return ModulesManager::instance().modules()[moduleName].at(id).i->getWidgetActionList()[waName].first;
}

/*
 * Возвращает дествие из списка действий модуля
 */
QAction *mod::getModuleAction_FromActionsList(QString moduleName, QString actionName, int id) {
  return ModulesManager::instance().modules()[moduleName].at(id).i->getActionList()[actionName];
}
