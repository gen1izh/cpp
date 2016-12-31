#include "managers.h"

// Инстанцирование объекта главного плагина
Core::Plugins &Core::Plugins::instance() {
    static Core::Plugins singleObject;
    return singleObject;
}

// Конструктор плагина
Core::Plugins::Plugins()
{
    setObjectName(tr("Главный менеджер"));
}

// Финализация главного плагина
int Core::Plugins::finalize() {
    QHashIterator<QString, PluginInterface *>  i(m_plugins);
    while (i.hasNext()) {
        i.next();
        delete i.value(); // Удаление плагина из памяти
    }
    return SUCCESSFUL;
}

// Возвращает указатель на объект журнала
ILoggerPlugin  *Core::Plugins::logger() const {
    if (m_iloggermanager.data()==NULL) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Журнал не подключен!"));
    }
    return m_iloggermanager.data();
}

/*!
 * \brief Возвращает хеш плагинов
 * \return
 */
QHash<QString, PluginInterface *> Core::Plugins::managers() const {
    if (m_plugins.isEmpty()) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Менеджеры отсутствуют!"));
    }
    return m_plugins;
}


// Возвращает указатель на объект загрузочного плагина
ISessionPlugin *Core::Plugins::boot() const {
    if (m_ibootmanager.data() == NULL) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Загрузчик не был корректно подключен!"));
    }
    return m_ibootmanager.data();
}

// Инициализация плагинов.
int Core::Plugins::load() {

    PluginInterface *pluginInterface;

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
        KleverGui::instance().splashMessage("Инициализация плагина \" " + pluginName + " \" ");

        // Загрузка, инстанцирование плагина.
        QPluginLoader loader(pluginName);
        QObject *pluginInstance = loader.instance();

        // Проверка факта инстанцирования.
        if (pluginInstance) {
            if (pluginName=="session") {
                m_ibootmanager.reset(qobject_cast<ISessionPlugin *>(pluginInstance));
                pluginInterface = static_cast<PluginInterface *>(m_ibootmanager.data());
            }
            else if (pluginName=="logger") {
                m_iloggermanager.reset(qobject_cast<ILoggerPlugin *>(pluginInstance));
                pluginInterface = static_cast<PluginInterface *>(m_iloggermanager.data());
            }
            else if (pluginName=="autorization") {
                m_iautorizationmanager.reset(qobject_cast<IAutorizationManager *>(pluginInstance));
                pluginInterface = static_cast<PluginInterface *>(m_iautorizationmanager.data());
            }
            else {
                pluginInterface = qobject_cast<PluginInterface *>(pluginInstance);
            }

            // Заполняем хеш плагинов
            m_plugins[pluginName] = pluginInterface;
        }
        else {
            messageLibrary msg;
            qDebug().noquote() << pluginName << ":" << loader.errorString();
            msg.createErrorMessage(tr(""), pluginName + tr(":") + loader.errorString());
            if (defaultPlugins.contains(pluginName)) {
                return MANAGERS_LOADING_ERROR;
            }
        }

        qDebug().noquote() << pluginName << " = " << pluginInterface;

    }

    return SUCCESSFUL;
}


// Создание действий плагинов
void Core::Plugins::createActions() {
    QHashIterator<QString, PluginInterface *>  i(m_plugins);
    while (i.hasNext()) {
        i.next();
        i.value()->createActions();
    }
}

// Проверка наличия плагина
bool Core::Plugins::isManagerExist(QString name) {
    QHashIterator<QString, PluginInterface *>  i(m_plugins);
    while (i.hasNext()) {
        i.next();
        if ( name == i.key() ) {
            return true;
        }
    }
    return false;
}

// Создание коннекторов плагинов
void Core::Plugins::createConnectors() {
    QHashIterator<QString, PluginInterface *>  i(m_plugins);
    while (i.hasNext()) {
        i.next();
        i.value()->createConnectors();
    }
}


// Создание виджетов для всех плагинов
void Core::Plugins::createWidgets() {
    // Журнал должен инициализироваться самым первым.
    m_plugins["logger"]->createWidgets();

    QHashIterator<QString, PluginInterface *>  i(m_plugins);
    while (i.hasNext()) {
        i.next();
        if (i.key()!="logger") {
            i.value()->createWidgets();
        }
    }
}
