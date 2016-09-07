#include "CveManager.h"

#include <frameWork/cve.h>
#include <QTimer>


using namespace Core;

/*
 * Инстанцирование объекта главного менеджера над менеджерами компонентов ядра
 */
CveManager &CveManager::instance() {
    static CveManager singleObject;
    return singleObject;
}

/*
 *  Инициализация менеджеров
 */
int CveManager::loadManagers() {

    ManagerInterface    *managerInterface;

    if (!isMainIniExist()) {
        return NO_MAIN_INI_ERROR;
    }

    // Чтение перечня менеджеров из настроек
    MainSetupApi mainsetup;
    QStringList  managersNamesList = mainsetup.getListKeysMainParam(QString("managers"));

    // Если менеджеры отсутствуют
    if (managersNamesList.isEmpty()) {
        // Создаем заглушку для загрузчика
        //        QScopedPointer<BootMock> _ibootmanager(new BootMock());
        //        _ibootmanager = new BootMock();
        //        managerInterface = static_cast<ManagerInterface *>(_ibootmanager);
        _ibootmanager.reset(new BootMock());
        _managers["boot"] = static_cast<ManagerInterface *>(_ibootmanager.data());

        // Создаем заглушку для журнала
        //        _iloggermanager = new LoggerMock();
        //        managerInterface = static_cast<ManagerInterface *>(_iloggermanager);
        _iloggermanager.reset(new LoggerMock());
        _managers["loggermock"] = static_cast<ManagerInterface *>(_iloggermanager.data());

        return NO_MANAGERS_ERROR;
    }

    foreach (QString manName, managersNamesList) {
        CveGui::instance().splashMessage("Инициализация менеджера \" " + manName + " \" ");

        QString state = mainsetup.getMainParam(QString("managers"),manName);

        if (state == "on") {
            QPluginLoader loader(manName);
            QObject *pluginInstance = loader.instance();

            if (pluginInstance) {
                if (manName=="boot") {
                    _ibootmanager.reset(qobject_cast<IBootManager *>(pluginInstance));
                    managerInterface = static_cast<ManagerInterface *>(_ibootmanager.data());
                }
                else if (manName=="logger") {
                    _iloggermanager.reset(qobject_cast<ILoggerManager *>(pluginInstance));
                    managerInterface = static_cast<ManagerInterface *>(_iloggermanager.data());
                }
                else {
                    managerInterface = qobject_cast<ManagerInterface *>(pluginInstance);
                }

                //TODO: boot и logger менеджеры тоже должны быть тут.
                //неоходимо проверить
                _managers[manName] = managerInterface; // Заполняем хеш менеджеров
            }
            else {
                messageLibrary msg;
                qDebug().noquote() << manName << ":" << loader.errorString();
                msg.createErrorMessage(tr(""), manName+tr(":")+loader.errorString());
                return MANAGERS_LOADING_ERROR;
            }

            qDebug().noquote() << manName << " = " << managerInterface;
        }
        else {
            if (manName=="boot") {
                //                _ibootmanager = new BootMock();
                //                managerInterface = static_cast<ManagerInterface *>(_ibootmanager);
                //                _managers["boot"] = managerInterface;
                _managers["boot"] = static_cast<ManagerInterface *>(_ibootmanager.data());
            }

            if (manName=="logger") {
                //                _iloggermanager = new LoggerMock();
                //                managerInterface = static_cast<ManagerInterface *>(_iloggermanager);
                //                _managers["loggermock"] = managerInterface;
                _managers["loggermock"] = static_cast<ManagerInterface *>(_iloggermanager.data());
            }
        }
    }

    return SUCCESSFUL;
}

/*
 * Финализация главного менеджера
 */
void CveManager::finalize() {
    QHashIterator<QString, ManagerInterface *>  i(_managers);
    while (i.hasNext()) {
        i.next();
        delete i.value(); // Удаление менеджера из памяти
    }
}

/*
 * Создание действий
 */
void CveManager::createActions() {
    QHashIterator<QString, ManagerInterface *>  i(_managers);
    while (i.hasNext()) {
        i.next();
        i.value()->createActions();
    }
}

/*
 * Создание коннекторов
 */
void CveManager::createConnectors() {
    QHashIterator<QString, ManagerInterface *>  i(_managers);
    while (i.hasNext()) {
        i.next();
        i.value()->createConnectors();
    }
}

/*
 * Создание виджетов для всех менеджеров
 */
void CveManager::createWidgets() {
    // Журнал должен инициализироваться самым первым.
    _managers["logger"]->createWidgets();

    QHashIterator<QString, ManagerInterface *>  i(_managers);
    while (i.hasNext()) {
        i.next();
        if (i.key()!="logger") {
            i.value()->createWidgets();
        }
    }
}
