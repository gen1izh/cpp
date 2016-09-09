#include "kapplication.h"

#include <frameWork/base.h>
#include <frameWork/gui/cvegui.h>
#include <core/frameWork/information.h>


QString KApplication::initPluginsPath() {
    // Устанавливает абсолютный адрес до каталога
    QDir pluginsDir(QCoreApplication::applicationDirPath());

#if defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    // Переход на каталог plugins
    pluginsDir.cd("modules");

    // Получение абсолютного пути до плагинов
    QString pluginsPath = pluginsDir.absolutePath();
    // Установка пути до плагинов
    QCoreApplication::addLibraryPath(pluginsPath);
    // Вывод в консоль путь до плагинов
    qDebug() << "Library paths:" << QCoreApplication::libraryPaths();

    return pluginsPath;
}

int KApplication::finalize()
{
    if (Core::Base::instance().finalize() != KAPP_SUCCESSFUL) {
        qDebug() << "System error[" << KAPP_SYSTEM_FINALIZE_ERROR << "]";
    }
    if (Core::CveGui::instance().finalize() != KAPP_SUCCESSFUL) {
        qDebug() << "System error[" << KAPP_GUI_FINALIZE_ERROR << "]";
    }
    return KAPP_SOME_ERROR;
}

void KApplication::readInformation()
{
    Information::instance();
    Information::instance().readApplicationInformation();
}

void KApplication::connect()
{
    QObject::connect(&Core::CveGui::instance(), SIGNAL(blockMainWindowByDialogSignal(QString)),
                   &Core::CveGui::instance(), SLOT(startDialog(QString)));

    QObject::connect(&Core::CveGui::instance(), SIGNAL(unblockMainWindowByDialogSignal()),
                   &Core::CveGui::instance(), SLOT(closeDialog()));
}

void KApplication::instanceTopManagers()
{
    // Инициализация базового компонента
    Core::Base::instance();

    // Инстанцирование главного менеджера
    Core::Managers::instance();

    // Инициализация менеджера ГИП
    Core::CveGui::instance();

    // Инициализация менеджера модулей
    Core::ModulesManager::instance();
}

void KApplication::setSplashScreenVisible(bool value)
{
    if (value) {
        // Инициализация сплеш-скрина
        Core::CveGui::instance().initializeSplashScreen();
    }
    else {
        // Отключение сплеш-скрина
        Core::CveGui::instance().finishSplashScreen();
    }
}

void KApplication::prepareStage1()
{
    // Создание действий
    Core::Managers::instance().createActions();
    // Создание виджетов
    Core::Managers::instance().createWidgets();
    // Создание коннекторов
    Core::Managers::instance().createConnectors();

    // Инициализация mainwindow и mdi
    Core::CveGui::instance().initializeMainwindowAndMdi();
}

void KApplication::prepareStage2()
{
    // Обновление информации о модулях
    Core::ModulesManager::instance().updateModulesList();

    // Инициализация менеджера форм.
    // INFO: Инициализация должна происходить после загрузки всех модулей.
    Core::CveGui::instance().initializeFormManager();

    // Подготовка ГИП
    Core::CveGui::instance().prepare();

    // Инициализация настроек
    Core::Base::instance().initializeSettings();

    // Отложенный запуск модулей
    Core::Base::instance().startModulesBy100ms();

    // При открытии окно будет максимального размера
    Core::CveGui::instance().showMaximized();
}

void KApplication::prepareStage3()
{
    // Восстановление позиции доков
    Core::CveGui::instance().restoreDocksPosition();
}
