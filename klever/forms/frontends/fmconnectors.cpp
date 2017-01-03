#include "formsManager.h"
#include "plug.h"

using namespace plug;

/*
 * Создание коннекторов для плагинов
 */
void FormsManager::createManagersConnections() {

  /*******************************************************************************
   *                  Менеджер тестовых последовательностей.
   *******************************************************************************/
  // Если менеджер журналирования подключен

  if (Core::Plugins::instance().isPluginExist(tr("logger"))) {
    connect( getManagerAction_FromWAPair(tr("logger"),
                                         tr("(Logger)Watcher")),
             SIGNAL(triggered()), this, SLOT(openLoggersWatcherWindow()) );
  }

  // Если менеджер тестовых последовательностей подключен
  if (Core::Plugins::instance().isPluginExist(tr("testsequence"))) {
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
  createManagersConnections();
}
