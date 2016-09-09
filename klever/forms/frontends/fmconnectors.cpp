#include "formsManager.h"
#include "man.h"

#include "mod.h"
using namespace man;
using namespace mod;

/*
 * Создание коннекторов для модулей
 */
void FormsManager::createModulesConnections() {
  connect( _controlAction, SIGNAL( triggered() ),
              this, SLOT( openControlWindow() ) );
}

/*
 * Создание коннекторов для менеджеров
 */
void FormsManager::createManagersConnections() {

  /*******************************************************************************
   *                  Менеджер тестовых последовательностей.
   *******************************************************************************/
  // Если менеджер журналирования подключен

  if (Core::Managers::instance().isManagerExist(tr("logger"))) {
    connect( getManagerAction_FromWAPair(tr("logger"),
                                         tr("(LoggerManager)loggersWatcherWidget")),
             SIGNAL(triggered()), this, SLOT(openLoggersWatcherWindow()) );
  }

  // Если менеджер тестовых последовательностей подключен
  if (Core::Managers::instance().isManagerExist(tr("testsequence"))) {
    connect(getManagerAction_FromWAPair(tr("testsequence"),
                                        tr("(TestSequenceManager)TestsequenceEditor")),
            SIGNAL(triggered()), this, SLOT( openTestSequenceTreeWindow() ) );

    connect(getManagerAction_FromWAPair(tr("testsequence"),
                                        tr("(TestSequenceManager)TestsequenceExecutor")),
            SIGNAL(triggered()), this, SLOT( openTestSequenceExecutorTreeWindow() ) );

  }
}

/*
 * Создание коннекторов
 */
void FormsManager::createConnections() {
  createModulesConnections();
  createManagersConnections();
}
