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
    QHashIterator<QString, ManagerInterface *>  i(m_plugins);
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
    if (m_plugins.isEmpty()) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Менеджеры отсутствуют!"));
    }
    return m_plugins;
}


// Возвращает указатель на объект загрузочного менеджера
ISessionManager *Core::Managers::boot() const {
    if (_ibootmanager.data() == NULL) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Загрузчик не был корректно подключен!"));
    }
    return _ibootmanager.data();
}

// Инициализация плагинов.
int Core::Managers::load() {

    ManagerInterface *managerInterface;

    // Формирование списка плагинов для загрузки по-умолчанию.
    QStringList  defaultPlugins;
    defaultPlugins << "session" << "logger" << "tube" << "autorization";

    // Формирование списка плагинов для загрузки. Из списка плагинов.
    QStringList  customPlugins;
    customPlugins.clear();  // TODO: надо сделать загрузку из БД.

    // Теперь customPlugins содержит оба списка.
    customPlugins += defaultPlugins;

    // Пробегаемся по всем плагинам.
    foreach (QString pluginName, customPlugins) {
        KleverGui::instance().splashMessage("Инициализация менеджера \" " + pluginName + " \" ");

        // Загрузка, инстанцирование плагина.
        QPluginLoader loader(pluginName);
        QObject *pluginInstance = loader.instance();

        // Проверка факта инстанцирования.
        if (pluginInstance) {
            if (pluginName=="session") {
                _ibootmanager.reset(qobject_cast<ISessionManager *>(pluginInstance));
                managerInterface = static_cast<ManagerInterface *>(_ibootmanager.data());
            }
            else if (pluginName=="logger") {
                _iloggermanager.reset(qobject_cast<ILoggerManager *>(pluginInstance));
                managerInterface = static_cast<ManagerInterface *>(_iloggermanager.data());
            }
            else {
                managerInterface = qobject_cast<ManagerInterface *>(pluginInstance);
            }

            // Заполняем хеш менеджеров
            m_plugins[pluginName] = managerInterface;
        }
        else {
            messageLibrary msg;
            qDebug().noquote() << pluginName << ":" << loader.errorString();
            msg.createErrorMessage(tr(""), pluginName + tr(":") + loader.errorString());
            if (defaultPlugins.contains(pluginName)) {
                return MANAGERS_LOADING_ERROR;
            }
        }

        qDebug().noquote() << pluginName << " = " << managerInterface;

    }

    return SUCCESSFUL;
}


// Создание действий менеджеров
void Core::Managers::createActions() {
    QHashIterator<QString, ManagerInterface *>  i(m_plugins);
    while (i.hasNext()) {
        i.next();
        i.value()->createActions();
    }
}

// Проверка наличия менеджера
bool Core::Managers::isManagerExist(QString name) {
    QHashIterator<QString, ManagerInterface *>  i(m_plugins);
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
    QHashIterator<QString, ManagerInterface *>  i(m_plugins);
    while (i.hasNext()) {
        i.next();
        i.value()->createConnectors();
    }
}


// Создание виджетов для всех менеджеров
void Core::Managers::createWidgets() {
    // Журнал должен инициализироваться самым первым.
    m_plugins["logger"]->createWidgets();

    QHashIterator<QString, ManagerInterface *>  i(m_plugins);
    while (i.hasNext()) {
        i.next();
        if (i.key()!="logger") {
            i.value()->createWidgets();
        }
    }
}
