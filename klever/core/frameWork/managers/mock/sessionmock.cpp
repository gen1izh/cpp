#include "sessionmock.h"

SessionMock::SessionMock()
{

}

SessionMock::~SessionMock()
{
    delete _wgt;
}

bool SessionMock::execute()
{
    qDebug() << "boot mock executed";

    Core::Base::instance().setParameterValue(QString("/sessionPath"), QDir::currentPath() );
    qDebug() << "Current path = " << QDir::currentPath();

    Core::Base::instance().setParameterValue(QString("/sessionName"), QString("NO_SESSION"));
    qDebug() << "SessionName = " << QString("NO_SESSION");

    return true;
}

QIcon SessionMock::settingIcon()
{
    return QIcon();
}

QWidget *SessionMock::getSettingPage()
{
    _wgt = new QWidget();
    return _wgt;
}

void SessionMock::createWidgets()
{
    qDebug() << "boot mock [createWidgets()]";
}

void SessionMock::createActions()
{
    qDebug() << "boot mock [createActions()]";
}

void SessionMock::createConnectors()
{
    qDebug() << "boot mock [createConnectors()]";
}
