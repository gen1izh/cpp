#include "managerinterface.h"

ManagerInterface::ManagerInterface()
{

}

ManagerInterface::~ManagerInterface()
{

}

void ManagerInterface::initialize(const QString &name, const QString textName)
{
    setName(name);
    setTextName(textName);

    checkManagerState();

    createWidgets();
    createActions();
    createConnectors();
}

void ManagerInterface::setName(const QString &name)
{
    m_name = name;
}

QString ManagerInterface::name() const
{
    return m_name;
}

void ManagerInterface::setTextName(const QString &name)
{
    m_textname = name;
}

QString ManagerInterface::textName() const
{
    return m_textname;
}

bool ManagerInterface::isOn() const
{
    return m_isOn;
}

bool ManagerInterface::isDisable() const
{
    return m_isDisable;
}

void ManagerInterface::setOnOrOff(bool flag)
{
    m_isOn = flag;
}

void ManagerInterface::checkManagerState()
{
    // По умолчанию отключаем менеджер
    setOnOrOff(false);

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("plugins");
    m_db.open();

    QDjango::setDatabase(m_db);
    QDjango::registerModel<PluginsQDjangoModel>();

    QDjango::createTables();

    QDjangoQuerySet<PluginsQDjangoModel> plugins;

    bool isFind = false;
    foreach (const PluginsQDjangoModel &plugin, plugins) {
        if (plugin.type() == "manager") {
            if (plugin.name() == this->name()) {
                isFind = true;
                if (plugin.state()) {
                    setOnOrOff(true);
                }
            }
        }
    }

    if (!isFind) {
        QScopedPointer<PluginsQDjangoModel> newManager(new PluginsQDjangoModel());
        newManager.data()->setName(this->name());
        newManager.data()->setType("manager");
        newManager.data()->setState(false);
        newManager.data()->setObjectsCount(0);
        newManager.data()->save();


    }


    m_db.close();
}

QHash<QString, QPair<QWidget *, QAction *> > ManagerInterface::getWidgetActionList() const
{
    return widgetActionList;
}

QHash<QString, QAction *> ManagerInterface::getActionList() const
{
    return actionList;
}
