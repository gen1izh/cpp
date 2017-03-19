#include "plugins.h"

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
    if (m_iloggermanager==NULL) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Журнал не подключен!"));
    }
    return m_iloggermanager;
}

/*!
 * \brief Возвращает хеш плагинов
 * \return
 */
QHash<QString, PluginInterface *> Core::Plugins::plugins() const {
    if (m_plugins.isEmpty()) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Менеджеры отсутствуют!"));
    }
    return m_plugins;
}


// Возвращает указатель на объект загрузочного плагина
ISessionPlugin *Core::Plugins::boot() const {
    if (m_ibootmanager == NULL) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Загрузчик не был корректно подключен!"));
    }
    return m_ibootmanager;
}

// Возвращает указатель на объект плагина авторизации
IAutorizationManager *Core::Plugins::autorization() const {
    if (m_iautorizationmanager == NULL) {
        messageLibrary msg;
        msg.createErrorMessage(tr("Ошибка"), tr("Плагин авторизации не был корректно подключен!"));
    }
    return m_iautorizationmanager;
}

// Подгржает список плагинов из БД
QStringList Core::Plugins::LoadListFromDatabase() {

    QStringList list;

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<PluginsQDjangoModel>();
    QDjango::createTables();
    QDjangoQuerySet<PluginsQDjangoModel> plugins;

    foreach (const PluginsQDjangoModel &plugin, plugins) {
        if (!plugin.name().trimmed().isEmpty()) {
            list << plugin.name();
        }
    }

    return list;
}

// Удаляем плагин из списка плагинов
void Core::Plugins::DeletePluginFromDatabase(const QString &plugin_name) {

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<PluginsQDjangoModel>();
    QDjango::createTables();

    QDjangoQuerySet<PluginsQDjangoModel> plugins;
    plugins = plugins.filter(QDjangoWhere("name", QDjangoWhere::Equals, plugin_name) );
    plugins.remove();

}

// Добавляем в список плагинов новый плагин
void Core::Plugins::AddNewPluginDatabase(const QString &plugin_name) {

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<PluginsQDjangoModel>();
    QDjango::createTables();

    QDjangoQuerySet<PluginsQDjangoModel> plugins;

    bool isFind = false;
    foreach (const PluginsQDjangoModel &plugin, plugins) {

            if (plugin.name() == plugin_name) {
                isFind = true;
                break;
            }
    }

    if (!isFind) {
        QScopedPointer<PluginsQDjangoModel> newPlugin(new PluginsQDjangoModel());
        newPlugin.data()->setName(plugin_name);
        newPlugin.data()->save();
    }
    else {
        // TODO... message
    }
}


// Инициализация плагинов.
int Core::Plugins::load() {

    PluginInterface *pluginInterface;

    // Формирование списка плагинов для загрузки по-умолчанию.
    QStringList  defaultPlugins;
    defaultPlugins << "session" << "logger" << "tube" << "autorization";
    AddNewPluginDatabase("session");
    AddNewPluginDatabase("logger");
    AddNewPluginDatabase("tube");
    AddNewPluginDatabase("autorization");

    // Формирование списка плагинов для загрузки. Из списка плагинов.
    QStringList  customPlugins;
    customPlugins.clear();

    customPlugins = LoadListFromDatabase();

    // Теперь customPlugins содержит оба списка.
    customPlugins += defaultPlugins;

    customPlugins.removeDuplicates();

    // Пробегаемся по всем плагинам.
    foreach (QString pluginName, customPlugins) {
        KleverGui::instance().splashMessage("Инициализация плагина \" " + pluginName + " \" ");

        // Загрузка, инстанцирование плагина.
        QPluginLoader loader(pluginName);
        QObject *pluginInstance = loader.instance();

        // Проверка факта инстанцирования.
        if (pluginInstance) {
            if (pluginName=="session") {
                m_ibootmanager = qobject_cast<ISessionPlugin *>(pluginInstance);
                pluginInterface = static_cast<PluginInterface *>(m_ibootmanager);
            }
            else if (pluginName=="logger") {
                m_iloggermanager = qobject_cast<ILoggerPlugin *>(pluginInstance);
                pluginInterface = static_cast<PluginInterface *>(m_iloggermanager);
            }
            else if (pluginName=="autorization") {
                m_iautorizationmanager = qobject_cast<IAutorizationManager *>(pluginInstance);
                pluginInterface = static_cast<PluginInterface *>(m_iautorizationmanager);
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
bool Core::Plugins::isPluginExist(QString name) {
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
