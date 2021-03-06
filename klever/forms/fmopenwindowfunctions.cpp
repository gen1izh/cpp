#include "formsManager.h"
/* Формы приложения. Менеджеры. */
#include "pluginForms/settings/settingsmdichild.h"
#include "pluginForms/moduleinfo/moduleinfomdichild.h"
#include "pluginForms/logger/loggerswatchermdichild.h"

/* Подключение статус бара главного окна */
#include <frameWork/gui/mainwindow/mainwindow.h>



/*******************************************************************************
 *                      Формы плагинов
 *******************************************************************************/

/*
 * Открытие дочернего окна с настройками приложения
 */
void FormsManager::openAppOptionsWindow() {

  Core::KleverGui::instance().openWindow<SettingsMdiChild,MainWindow>(
        "APP_CONFIG_WINDOW", tr("Настройки приложения"),
        tr("Окно настроек приложения было успешно открыто."),
        tr("Окно настроек приложения не было успешно открыто!") );
}

/*
 * Открытие дочернего окна с информацией о модулях
 */
void FormsManager::openPluginInfoWindow() {

  Core::KleverGui::instance().openWindow<PluginInfoMdiChild,MainWindow>(
        "PLUGIN_INFO_WINDOW", tr("О плагинах"),
        tr("Окно плагинов системы было успешно открыто."),
        tr("Окно плагинов системы не было успешно открыто!") );
}


/*
 * Открытие дочернего окна просмотра журналов сообщений
 */
void FormsManager::openLoggersWatcherWindow() {

  Core::KleverGui::instance().openWindow<LoggersWatcherMdiChild,MainWindow>(
        "LOGGERS_WATCHER_WINDOW", tr("Просмотрщик журналов"),
        tr("Окно просмотрщика журналов было успешно открыто."),
        tr("Окно просмотрщика журналов не было успешно открыто!") );
}

