#include "plug.h"

// Возвращает действие из списка пар (виджет,действие)
QAction *plug::getManagerAction_FromWAPair(const QString &pluginName,
                                           const QString &waName) {
  return Core::Plugins::instance().plugins().value(pluginName)
          ->widgetActionList().value(waName).second;
}


// Возвращает виджет из списка пар (виджет,действие)
QWidget *plug::getManagerWidget_FromWAPair(const QString &pluginName,
                                           const QString &waName) {
  return Core::Plugins::instance().plugins().value(pluginName)
          ->widgetActionList().value(waName).first;
}

// Возвращает дествие из списка действий плагина
QAction *plug::getManagerAction_FromActionsList(const QString &pluginName,
                                                const QString &actionName) {
  return Core::Plugins::instance().plugins().value(pluginName)
          ->actionList()[actionName];
}


// Возвращает действие из списка пар (виджет,действие)
QAction *plug::getLoggerAction_FromWAPair(const QString &waName) {
  return Core::Plugins::instance().logger()->widgetActionList().value(waName).second;
}


// Возвращает виджет из списка пар (виджет,действие)
QWidget *plug::getLoggerWidget_FromWAPair(const QString &waName) {
  return Core::Plugins::instance().logger()->widgetActionList().value(waName).first;
}


// Возвращает дествие из списка действий плагина
QAction *plug::getLoggerAction_FromActionsList(const QString &waName) {
  return Core::Plugins::instance().logger()->actionList().value(waName);
}


