#include "formsManager.h"
#include "man.h"

#include "mod.h"
using namespace man;
using namespace mod;

/*
 * Создание меню модулей
 */
void FormsManager::createModulesMenu() {

  /*******************************************************************************
   *                  Модуль источника питания
   *******************************************************************************/

  QMenu *controlMenu = _complexMenu->addMenu(tr("&Управление"));
  controlMenu->addAction(_controlAction);
}

/*
 * Создание меню менеджеров
 */
void FormsManager::createManagersMenu() {

  /*******************************************************************************
   *                  Менеджер тестовых последовательностей.
   *******************************************************************************/

    if (Core::CveManager::instance().isManagerExist(tr("logger"))) {
      QMenu *loggerMenu = _managersMenu->addMenu(tr("&Журнал"));
      loggerMenu->addAction(getManagerAction_FromWAPair("logger",
                                                              "(LoggerManager)loggersWatcherWidget"));
    }

  if (Core::CveManager::instance().isManagerExist(tr("testsequence"))) {
    // Создание меню "Тестовые последовательности"
    QMenu *testsequenceMenu = _managersMenu->addMenu(tr("&Тестовые последовательности"));

    testsequenceMenu->addSeparator();

    QMenu *controlTestsequenceMenu = testsequenceMenu->addMenu(tr("&Операции редактирования"));
    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "createAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "saveAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "addAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "deleteAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "cutAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "pasteAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "editAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "upAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "downAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "promoteAction"));

    controlTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",
                                                                        "demoteAction"));

    QMenu *executeTestsequenceMenu = testsequenceMenu->addMenu(tr("&Исполнение"));

    // TODO: Не реализовано в executor




//    executeTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",

//                                                                        "startAction"));

//    executeTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",

//                                                                        "pauseAction"));

//    executeTestsequenceMenu->addAction(getManagerAction_FromActionsList("testsequence",

//                                                                        "stopAction"));
  }

}


/*
 * Создает меню комплесных форм
 */
void FormsManager::createMenu() {
  if (Core::CveManager::instance().boot()->hasRightUser(CAN_SEE_MODULES_MENU)) {
    _modulesMenu  =  Core::CveGui::instance().mainwindow()->menuBar()->addMenu(tr("&Модули"));
    _complexMenu  =  Core::CveGui::instance().mainwindow()->menuBar()->addMenu(tr("&Комплексные окна"));
    createModulesMenu();
  }

  if (Core::CveManager::instance().boot()->hasRightUser(CAN_SEE_MANAGERS_MENU)) {
    _managersMenu =  Core::CveGui::instance().mainwindow()->menuBar()->addMenu(tr("&Менеджеры"));
    createManagersMenu();
  }
}
