#include "CveManager.h"

// Инстанцирование объекта главного менеджера
Core::CveManager &Core::CveManager::instance() {
    static Core::CveManager singleObject;
    return singleObject;
}

// Конструктор менеджера
Core::CveManager::CveManager()
{
    setObjectName(tr("Главный менеджер"));
}

// Финализация главного менеджера
int Core::CveManager::finalize() {
    QHashIterator<QString, ManagerInterface *>  i(m_managers);
    while (i.hasNext()) {
        i.next();
        delete i.value(); // Удаление менеджера из памяти
    }
    return SUCCESSFUL;
}

// Возвращает указатель на объект журнала
ILoggerManager  *Core::CveManager::logger() const {
    if (_iloggermanager.data()==NULL) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Журнал не подключен!"));
    }
    return _iloggermanager.data();
}

/*!
 * \brief Возвращает хеш менеджеров
 * \return
 */
QHash<QString, ManagerInterface *> Core::CveManager::managers() const {
    if (m_managers.isEmpty()) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Менеджеры отсутствуют!"));
    }
    return m_managers;
}


// Возвращает указатель на объект загрузочного менеджера

IBootManager  *Core::CveManager::boot() const {
    if (_ibootmanager.data()==NULL) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Загрузчик не был корректно подключен!"));
    }
    return _ibootmanager.data();
}

// Инициализация менеджеров
int Core::CveManager::load() {

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
        _ibootmanager.reset(new BootMock());
        m_managers["boot"] = static_cast<ManagerInterface *>(_ibootmanager.data());

        // Создаем заглушку для журнала
        _iloggermanager.reset(new LoggerMock());
        m_managers["loggermock"] = static_cast<ManagerInterface *>(_iloggermanager.data());

        return NO_MANAGERS_ERROR;
    }

    // Пробегаемся по всем менеджерам
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
                m_managers[manName] = managerInterface; // Заполняем хеш менеджеров
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
                m_managers["boot"] = static_cast<ManagerInterface *>(_ibootmanager.data());
            }
            else if (manName=="logger") {
                m_managers["loggermock"] = static_cast<ManagerInterface *>(_iloggermanager.data());
            }
            else {
                qDebug().noquote() << "manager " << manName << " is off.";
            }
        }
    }

    return SUCCESSFUL;
}


// Создание действий менеджеров
void Core::CveManager::createActions() {
    QHashIterator<QString, ManagerInterface *>  i(m_managers);
    while (i.hasNext()) {
        i.next();
        i.value()->createActions();
    }
}

// Проверка наличия менеджера
bool Core::CveManager::isManagerExist(QString name) {
    QHashIterator<QString, ManagerInterface *>  i(m_managers);
    while (i.hasNext()) {
        i.next();
        if ( name == i.key() ) {
            return true;
        }
    }
    return false;
}

// Создание коннекторов менеджеров
void Core::CveManager::createConnectors() {
    QHashIterator<QString, ManagerInterface *>  i(m_managers);
    while (i.hasNext()) {
        i.next();
        i.value()->createConnectors();
    }
}


// Создание виджетов для всех менеджеров
void Core::CveManager::createWidgets() {
    // Журнал должен инициализироваться самым первым.
    m_managers["logger"]->createWidgets();

    QHashIterator<QString, ManagerInterface *>  i(m_managers);
    while (i.hasNext()) {
        i.next();
        if (i.key()!="logger") {
            i.value()->createWidgets();
        }
    }
}
