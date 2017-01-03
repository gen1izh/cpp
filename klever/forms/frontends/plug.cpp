#include "plug.h"

/*
 * Возвращает действие из списка пар (виджет,действие)
 */
QAction *plug::getManagerAction_FromWAPair(QString pluginName, QString waName) {
  return Core::Plugins::instance().managers().value(pluginName)->getWidgetActionList().value(waName).second;
}

/*
 * Возвращает виджет из списка пар (виджет,действие)
 */
QWidget *plug::getManagerWidget_FromWAPair(QString pluginName, QString waName) {
  return Core::Plugins::instance().managers().value(pluginName)->getWidgetActionList().value(waName).first;
}

/*
 * Возвращает дествие из списка действий плагина
 */
QAction *plug::getManagerAction_FromActionsList(QString pluginName, QString actionName) {
  return Core::Plugins::instance().managers().value(pluginName)->getActionList()[actionName];
}

/*
 * Возвращает действие из списка пар (виджет,действие)
 */
QAction *plug::getLoggerAction_FromWAPair(QString waName) {
  return Core::Plugins::instance().logger()->getWidgetActionList().value(waName).second;
}

/*
 * Возвращает виджет из списка пар (виджет,действие)
 */
QWidget *plug::getLoggerWidget_FromWAPair(QString waName) {
  return Core::Plugins::instance().logger()->getWidgetActionList().value(waName).first;
}

/*
 * Возвращает дествие из списка действий плагина
 */
QAction *plug::getLoggerAction_FromActionsList(QString waName) {
  return Core::Plugins::instance().logger()->getActionList().value(waName);
}


