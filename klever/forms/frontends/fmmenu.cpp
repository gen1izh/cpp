#include "formsManager.h"
#include "plug.h"

using namespace plug;

/*
 * Создание меню плагинов
 */
void FormsManager::createManagersMenu() {

  /*******************************************************************************
   *                  Менеджер тестовых последовательностей.
   *******************************************************************************/

    if (Core::Plugins::instance().isPluginExist(tr("logger"))) {
      QMenu *loggerMenu = _managersMenu->addMenu(tr("&Журнал"));
      loggerMenu->addAction(getManagerAction_FromWAPair("logger",
                                                              "(Logger)Watcher"));
    }

  if (Core::Plugins::instance().isPluginExist(tr("testsequence"))) {
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
//  if (Core::Managers::instance().boot()->hasRightUser(CAN_SEE_MODULES_MENU)) {
//    _modulesMenu  =  Core::KleverGui::instance().mainwindow()->menuBar()->addMenu(tr("&Модули"));
//    _complexMenu  =  Core::KleverGui::instance().mainwindow()->menuBar()->addMenu(tr("&Комплексные окна"));
//    createModulesMenu();
//  }

//  if (Core::Managers::instance().boot()->hasRightUser(CAN_SEE_MANAGERS_MENU)) {
//    _managersMenu =  Core::KleverGui::instance().mainwindow()->menuBar()->addMenu(tr("&Менеджеры"));
//    createManagersMenu();
//  }
}
