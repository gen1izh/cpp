#include "formsManager.h"
/* Формы приложения. Менеджеры. */
#include "pluginForms/settings/settingsmdichild.h"
#include "pluginForms/moduleinfo/moduleinfomdichild.h"
#include "pluginForms/logger/loggerswatchermdichild.h"

/* Подключение статус бара главного окна */
#include <frameWork/gui/mainwindow/mainwindow.h>

#include "pluginForms/bf/analizemdichild.h"
#include "pluginForms/bf/architectmdichild.h"
#include "pluginForms/bf/deploybuildmdichild.h"
#include "pluginForms/bf/documentsmdichild.h"

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







/*
 * Открытие дочернего окна анализа требований
 */
void FormsManager::openAnalysisWindow() {

  Core::KleverGui::instance().openWindow<AnalysisMdiChild,MainWindow>(
        "ANALYSIS_WINDOW", tr("Анализ требований"),
        tr("Окно анализа требований было успешно открыто."),
        tr("Окно анализа требований не было успешно открыто!") );
}


/*
 * Открытие дочернего окна структуры системы
 */
void FormsManager::openArchitectWindow() {

  Core::KleverGui::instance().openWindow<ArchitectMdiChild,MainWindow>(
        "ARCHITECT_WINDOW", tr("Структура системы"),
        tr("Окно структуры системы было успешно открыто."),
        tr("Окно структуры системы не было успешно открыто!") );
}

/*
 * Открытие дочернего окна сборки установщика
 */
void FormsManager::openDeployBuildWindow() {

  Core::KleverGui::instance().openWindow<DeployBuildMdiChild,MainWindow>(
        "DEPLOY_BUIDLER_WINDOW", tr("Сборка установщика"),
        tr("Окно сборки установщика было успешно открыто."),
        tr("Окно сборки установщика не было успешно открыто!") );
}

/*
 * Открытие дочернего окна документации
 */
void FormsManager::openDocumentsWindow() {

  Core::KleverGui::instance().openWindow<DocumentsMdiChild,MainWindow>(
        "DOCUMENTS_WATCHER_WINDOW", tr("Документация"),
        tr("Окно документации было успешно открыто."),
        tr("Окно документации не было успешно открыто!") );
}
