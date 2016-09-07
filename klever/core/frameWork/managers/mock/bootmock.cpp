#include "bootmock.h"

BootMock::BootMock()
{

}

BootMock::~BootMock()
{
    delete _wgt;
}

bool BootMock::hasRightUser(int r)
{
    Q_UNUSED(r)
    return true;
}

bool BootMock::execute()
{
    qDebug() << "BootMock executed...";

    qDebug() << "============================ ";

    Cve::instance().setParameterValue(QString("/sessionPath"), QDir::currentPath() );
    qDebug() << "Current path = " << QDir::currentPath();

    Cve::instance().setParameterValue(QString("/rights"), QString("ALL"));
    qDebug() << "Rights = " << QString("ALL");

    Cve::instance().setParameterValue(QString("/sessionName"), QString("NO_SESSION"));
    qDebug() << "SessionName = " << QString("NO_SESSION");

    Cve::instance().setParameterValue(QString("/productType"), QString("NONE"));
    qDebug() << "ProductType = " << QString("NONE");

    Cve::instance().setParameterValue(QString("/serialNumber"), QString("1234"));
    qDebug() << "SerialNumber = " << QString("1234");

    qDebug() << "============================ ";

    return true;
}

QIcon BootMock::settingIcon()
{
    return QIcon();
}

QWidget *BootMock::getSettingPage()
{
    _wgt = new QWidget();
    return _wgt;
}

void BootMock::createWidgets()
{
    qDebug() << "BootMock::createWidgets()";
}

void BootMock::createActions()
{
    qDebug() << "BootMock::createActions()";
}

void BootMock::createConnectors()
{
    qDebug() << "BootMock::createConnectors()";
}
