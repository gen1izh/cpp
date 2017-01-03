#include "formsManager.h"
#include "plug.h"

using namespace plug;

/*
 * Создает панель быстрого запуска
 */
void FormsManager::createToolBar() {
    QToolBar *pluginsBar = Core::KleverGui::instance().mainwindow()->addToolBar(tr("Плагины"));
    pluginsBar->setObjectName("Плагины");
    pluginsBar->setIconSize(QSize(32,32));

    if (Core::Plugins::instance().isPluginExist(tr("logger"))) {
      pluginsBar->addAction(getManagerAction_FromWAPair(tr("logger"), tr("(Logger)Watcher")));
    }
}
