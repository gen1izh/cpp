#include <QDebug>
#include <QPixmap>
#include <QSplashScreen>
#include <QtWidgets>

#include "kapplication.h"
#include "singleapplication.h"

int main(int argc, char *argv[]) {

    // Инициализация класса приложения.
    // SingleApplication дает инициализировать один экзмпляр приложения.
    SingleApplication a(argc, argv);

    // Подключение ресурсов приложения.
    Q_INIT_RESOURCE(framework_resources);
    Q_INIT_RESOURCE(cvesettingsmanager_resources);
    Q_INIT_RESOURCE(lamplib_resources);

    // Настройка шаблона сообщения выводимого в консоль.
    qSetMessagePattern(
        "%{if-debug}[D]%{endif}%{if-warning}[W]%{endif}%{if-critical}[C]"
        "%{endif}%{if-fatal}[F]%{endif} [%{time hh:mm:ss}]%{if-category} "
        "[%{category}]%{endif} [%{file} : %{line}]   *** %{message} ***" );

    // Настройка кодировки приложения.
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // Инициализация путей к плагинам приложения.
    KApplication::initPluginsPath();

    // Инстанцирование всех главных плагинов.
    KApplication::instanceTopManagers();

    // Создание коннекторов.
    KApplication::connect();

    // Включить сплеш-скрин приложения.
    KApplication::setSplashScreenVisible(true);

    // Загрузка плагинов.
    if (Core::Plugins::instance().load()) {
        return -1;
    }

    // Запуск загрузчика.
    // Если загрузчик выполнился с ошибкой, то прекращает работу с приложением.
    if (!Core::Plugins::instance().boot()->execute()) {
        int kCode = KApplication::finalize();
        return kCode;
    }

    // Запуск авторизации.
    // Если авторизация прошла с ошибкой, то прекращает работу с приложением.
    if (!Core::Plugins::instance().autorization()->execute()) {
        int kCode = KApplication::finalize();
        return kCode;
    }

    // Подготовка. Стадия 1.
    KApplication::prepareStage1();

    // Подготовка. Стадия 2.
    KApplication::prepareStage2();

    // Отключаем сплеш-скрин.
    // Считается что все компоненты подгрузились.
    KApplication::setSplashScreenVisible(false);

    // Подготовка. Стадия 3.
    KApplication::prepareStage3();

    // Запустить приложение.
    int retVal = a.exec();

    qDebug() << " Application exit code: " << retVal;

    int kCode = KApplication::finalize();

    return kCode;
}

