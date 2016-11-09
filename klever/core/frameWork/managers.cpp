#include "managers.h"

// Инстанцирование объекта главного менеджера
Core::Managers &Core::Managers::instance() {
    static Core::Managers singleObject;
    return singleObject;
}

// Конструктор менеджера
Core::Managers::Managers()
{
    setObjectName(tr("Главный менеджер"));
}

// Финализация главного менеджера
int Core::Managers::finalize() {
    QHashIterator<QString, ManagerInterface *>  i(m_managers);
    while (i.hasNext()) {
        i.next();
        delete i.value(); // Удаление менеджера из памяти
    }
    return SUCCESSFUL;
}

// Возвращает указатель на объект журнала
ILoggerManager  *Core::Managers::logger() const {
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
QHash<QString, ManagerInterface *> Core::Managers::managers() const {
    if (m_managers.isEmpty()) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Менеджеры отсутствуют!"));
    }
    return m_managers;
}


// Возвращает указатель на объект загрузочного менеджера

ISessionManager  *Core::Managers::boot() const {
    if (_ibootmanager.data()==NULL) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Загрузчик не был корректно подключен!"));
    }
    return _ibootmanager.data();
}

// Инициализация менеджеров
int Core::Managers::load() {

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
        _ibootmanager.reset(new SessionMock());
        m_managers["boot"] = static_cast<ManagerInterface *>(_ibootmanager.data());

        // Создаем заглушку для журнала
        _iloggermanager.reset(new LoggerMock());
        m_managers["loggermock"] = static_cast<ManagerInterface *>(_iloggermanager.data());

        return NO_MANAGERS_ERROR;
    }

    // Пробегаемся по всем менеджерам
    foreach (QString manName, managersNamesList) {
        KleverGui::instance().splashMessage("Инициализация менеджера \" " + manName + " \" ");

        QString state = mainsetup.getMainParam(QString("managers"),manName);

        if (state == "on") {
            QPluginLoader loader(manName);
            QObject *pluginInstance = loader.instance();

            if (pluginInstance) {
                if (manName=="boot") {
                    _ibootmanager.reset(qobject_cast<ISessionManager *>(pluginInstance));
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
void Core::Managers::createActions() {
    QHashIterator<QString, ManagerInterface *>  i(m_managers);
    while (i.hasNext()) {
        i.next();
        i.value()->createActions();
    }
}

// Проверка наличия менеджера
bool Core::Managers::isManagerExist(QString name) {
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
void Core::Managers::createConnectors() {
    QHashIterator<QString, ManagerInterface *>  i(m_managers);
    while (i.hasNext()) {
        i.next();
        i.value()->createConnectors();
    }
}


// Создание виджетов для всех менеджеров
void Core::Managers::createWidgets() {
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
