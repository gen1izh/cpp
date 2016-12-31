#include "formsManager.h"
/* Формы приложения. Менеджеры. */
#include "managers/settings/settingsmdichild.h"
#include "managers/testsequence/testsequencetreemdichild.h"
#include "managers/testsequence/testsequenceexecutortreemdichild.h"
#include "managers/moduleinfo/moduleinfomdichild.h"
#include "managers/logger/loggerswatchermdichild.h"

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
 * Открытие дочернего окна с деревом проверок. Редактирование.
 */
void FormsManager::openTestSequenceTreeWindow() {

  Core::KleverGui::instance().openWindow<TestSequenceMdiChild,MainWindow>(
        "TEST_SEQUENCE_TREE_WINDOW", tr("Редактор тестовой последовательности"),
        tr("Окно редактора тестовой последовательности было успешно открыто."),
        tr("Окно редактора тестовой последовательности не было успешно открыто!") );
}

/*
 * Открытие дочернего окна с деревом проверок. Исполнение.
 */
void FormsManager::openTestSequenceExecutorTreeWindow() {
  Core::KleverGui::instance().openWindow<TestsequenceExecutorMdiChild,MainWindow>(
        "TEST_SEQUENCE_EXECUTOR_TREE_WINDOW", tr("Исполнение теста"),
        tr("Окно исполнения тестовой последовательности было успешно открыто."),
        tr("Окно исполнения тестовых последовательности не было успешно открыто!") );
}



/*
 * Открытие дочернего окна с информацией о модулях
 */
void FormsManager::openModuleInfoWindow() {

  Core::KleverGui::instance().openWindow<ModuleInfoMdiChild,MainWindow>(
        "MODULE_INFO_WINDOW", tr("О модулях"),
        tr("Окно модулей системы было успешно открыто."),
        tr("Окно модулей системы не было успешно открыто!") );
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

