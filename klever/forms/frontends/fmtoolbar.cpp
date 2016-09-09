#include "formsManager.h"
#include "man.h"
#include "mod.h"

using namespace man;
using namespace mod;

/*
 * Создание панели быстрого запуска для модулей
 */
void FormsManager::createModulesToolBar() {

  /*******************************************************************************
   *                  Модуль источника питания
   *******************************************************************************/

  QToolBar *controlToolBar = Core::CveGui::instance().mainwindow()->addToolBar(tr("Управление"));
  controlToolBar->setObjectName(tr("Управление"));
  Core::CveGui::instance().mainwindow()->addToolBar(Qt::RightToolBarArea,controlToolBar);
  controlToolBar->setAllowedAreas( Qt::RightToolBarArea );
  controlToolBar->addAction(_controlAction);
  controlToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  controlToolBar->setIconSize(QSize(50,50));

}

/*
 * Создание панели быстрого запуска для менеджеров
 */
void FormsManager::createManagersToolBar() {

  QToolBar *managersToolBar = Core::CveGui::instance().mainwindow()->addToolBar(tr("Менеджеры"));
  managersToolBar->setObjectName("Менеджеры");
  managersToolBar->setIconSize(QSize(32,32));

  /*******************************************************************************
   *                  Менеджер журналирования
   *******************************************************************************/

  if (Core::Managers::instance().isManagerExist(tr("logger"))) {
    managersToolBar->addAction(getManagerAction_FromWAPair(tr("logger"),
                                                           tr("(LoggerManager)loggersWatcherWidget")));
  }

  /*******************************************************************************
   *                  Менеджер тестовых последовательностей.
   *******************************************************************************/

  if (Core::Managers::instance().isManagerExist(tr("testsequence"))) {
  }
}

/*
 * Создает панель быстрого запуска
 */
void FormsManager::createToolBar() {
  if (Core::Managers::instance().boot()->hasRightUser(CAN_SEE_MODULES_TOOLBAR)) {
    createModulesToolBar();
  }
  if (Core::Managers::instance().boot()->hasRightUser(CAN_SEE_MANAGERS_TOOLBAR)) {
    createManagersToolBar();
  }
}
