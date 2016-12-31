#include "formsManager.h"
#include "man.h"

using namespace man;

/*
 * Создание панели быстрого запуска для плагинов
 */
void FormsManager::createManagersToolBar() {

  QToolBar *managersToolBar = Core::KleverGui::instance().mainwindow()->addToolBar(tr("Менеджеры"));
  managersToolBar->setObjectName("Менеджеры");
  managersToolBar->setIconSize(QSize(32,32));

  /*******************************************************************************
   *                  Менеджер журналирования
   *******************************************************************************/

  if (Core::Plugins::instance().isManagerExist(tr("logger"))) {
    managersToolBar->addAction(getManagerAction_FromWAPair(tr("logger"),
                                                           tr("(LoggerManager)loggersWatcherWidget")));
  }

  /*******************************************************************************
   *                  Менеджер тестовых последовательностей.
   *******************************************************************************/

  if (Core::Plugins::instance().isManagerExist(tr("testsequence"))) {
  }
}

/*
 * Создает панель быстрого запуска
 */
void FormsManager::createToolBar() {
//  if (Core::Managers::instance().boot()->hasRightUser(CAN_SEE_MODULES_TOOLBAR)) {
//    createModulesToolBar();
//  }
//  if (Core::Managers::instance().boot()->hasRightUser(CAN_SEE_MANAGERS_TOOLBAR)) {
//    createManagersToolBar();
//  }
}
