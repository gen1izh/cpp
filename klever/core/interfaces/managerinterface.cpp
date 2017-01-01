#include "managerinterface.h"
#include <QDebug>
#include <QCoreApplication>
#include <library/message/messagelibrary.h>

PluginInterface::PluginInterface()
{

}

PluginInterface::~PluginInterface()
{

}

void PluginInterface::initialize(const QString &name, const QString textName)
{
    setName(name);
    setTextName(textName);

    checkManagerState();

    createWidgets();
    createActions();
    createConnectors();
}

void PluginInterface::setName(const QString &name)
{
    m_name = name;
}

QString PluginInterface::name() const
{
    return m_name;
}

void PluginInterface::setTextName(const QString &name)
{
    m_textname = name;
}

QString PluginInterface::textName() const
{
    return m_textname;
}

bool PluginInterface::isOn() const
{
    return m_isOn;
}

bool PluginInterface::isDisable() const
{
    return m_isDisable;
}

void PluginInterface::setOnOrOff(bool flag)
{
    m_isOn = flag;
}

void PluginInterface::checkManagerState()
{
    // По умолчанию отключаем менеджер
    setOnOrOff(true);

    m_db = QSqlDatabase::database("plugininterface");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "plugininterface");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__plugins");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);
    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<PluginsQDjangoModel>();

        QDjango::createTables();

        QDjangoQuerySet<PluginsQDjangoModel> plugins;

        bool isFind = false;
        foreach (const PluginsQDjangoModel &plugin, plugins) {
            if (plugin.type() == "manager") {
                if (plugin.name() == this->name()) {
                    isFind = true;
                    if (plugin.state() == "on") {
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

    }
    m_db.close();
}

QHash<QString, QPair<QWidget *, QAction *> > PluginInterface::getWidgetActionList() const
{
    return widgetActionList;
}

QHash<QString, QAction *> PluginInterface::getActionList() const
{
    return actionList;
}
