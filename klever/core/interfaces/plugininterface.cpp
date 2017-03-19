#include "plugininterface.h"
#include <QDebug>
#include <QCoreApplication>
#include <library/message/messagelibrary.h>
#include <frameWork/base.h>

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

void PluginInterface::checkManagerState()
{
//    {
//    QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC", "loadplugins");
//    m_db.setDatabaseName("DRIVER={SQL Server};SERVER=.\\SQLEXPRESS;DATABASE=__PLUGINS;Trusted_Connection=yes;");
//    m_db.setUserName("sa");
//    ;

//    if (!m_db.open()) {
//        messageLibrary msg;
//        QString text;
//        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

//        msg.createErrorMessage("Ошибка", text);
//    }
//    else {

//        QDjango::setDatabase(m_db);
        QDjango::setDatabase(*Core::Base::instance().database());
        QDjango::registerModel<PluginsQDjangoModel>();

        QDjango::createTables();

        QDjangoQuerySet<PluginsQDjangoModel> plugins;

        bool isFind = false;
        foreach (const PluginsQDjangoModel &plugin, plugins) {

                if (plugin.name() == this->name()) {
                    isFind = true;
                }
        }

        if (!isFind) {
            QScopedPointer<PluginsQDjangoModel> newManager(new PluginsQDjangoModel());
            newManager.data()->setName(this->name());
            newManager.data()->save();


        }

//    }
//    m_db.close();
//    }
//    QSqlDatabase::removeDatabase("loadplugins");
}

QHash<QString, QPair<QWidget *, QAction *> > PluginInterface::widgetActionList() const
{
    return _widgetActionList;
}

QHash<QString, QAction *> PluginInterface::actionList() const
{
    return _actionList;
}
