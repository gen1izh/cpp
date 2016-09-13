#include <QDebug>
#include <QPixmap>
#include <QSplashScreen>
#include <QtWidgets>

#include "kapplication.h"
#include "singleapplication.h"

//// Подключение основного класс приложения MainWindow
//#include <core/frameWork/gui/mainwindow/mainwindow.h>


// Тело основной функции программы
int main(int argc, char *argv[]) {

    // Инициализация класса приложения
    SingleApplication a(argc, argv);

    // Подключение ресурсов приложения
    Q_INIT_RESOURCE(framework_resources);
    Q_INIT_RESOURCE(cvesettingsmanager_resources);
    Q_INIT_RESOURCE(lamplib_resources);

    // Настройка шаблона сообщения выводимого в консоль
    qSetMessagePattern(
        "%{if-debug}[D]%{endif}%{if-warning}[W]%{endif}%{if-critical}[C]"
        "%{endif}%{if-fatal}[F]%{endif} [%{time hh:mm:ss}]%{if-category} "
        "[%{category}]%{endif} [%{file} : %{line}]   *** %{message} ***" );

    // Настройка кодировки приложения
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // Чтение информации
    KApplication::readInformation();

    // Инициализация путей к плагинам приложения
    KApplication::initPluginsPath();

    // Инстанцирование всех главных менеджеров
    KApplication::instanceTopManagers();

    // Создание коннекторов
    KApplication::connect();

    // Включить сплеш-скрин
    KApplication::setSplashScreenVisible(true);

    // Загрузка менеджеров
    int result = Core::Managers::instance().load();

    // Если файла main.ini нет, то смысла продолжать исполнения программы - нет.
    // В этом случае пользователь должен запустить конфигуратор.
    if (result==Core::NO_MAIN_INI_ERROR) {
        return -1;
    }

    // Запуск загрузчика
    if (!Core::Managers::instance().boot()->execute()) {

        int kCode = KApplication::finalize();
        return kCode;
    }

    KApplication::prepareStage1();

    // Чтение каталога с модулями
    Core::ModulesManager::instance().load();

    KApplication::prepareStage2();

    KApplication::setSplashScreenVisible(false);

    KApplication::prepareStage3();

    // Запустить приложение
    int retVal = a.exec();

    qDebug() << " Application exit code: " << retVal;

    int kCode = KApplication::finalize();

    return kCode;
}

