#ifndef BOOTMOCK_H
#define BOOTMOCK_H
#include <QDebug>
#include <QString>

#include "interfaces/ibootmanager.h"
#include <frameWork/cve.h>

class BootMock : public IBootManager
{
  QWidget *_wgt;

  public:
    BootMock();
    ~BootMock();

    bool hasRightUser(int r) {
      Q_UNUSED(r)
      return true;
    }

    bool execute() {
      qDebug() << "bootloader executed";

      Cve::instance().setParameterValue(QString("/sessionPath"), QDir::currentPath() );
      qDebug() << "current path = " << QDir::currentPath();

      Cve::instance().setParameterValue(QString("/rights"), QString("ALL"));
      qDebug() << "rights = " << QString("ALL");

      Cve::instance().setParameterValue(QString("/sessionName"), QString("NO_SESSION"));
      qDebug() << "sessionName = " << QString("NO_SESSION");

      Cve::instance().setParameterValue(QString("/productType"), QString("NONE"));
      qDebug() << "productType = " << QString("NONE");

      Cve::instance().setParameterValue(QString("/serialNumber"), QString("1234"));
      qDebug() << "serialNumber = " << QString("1234");

      return true;
    }

    QIcon settingIcon() {
      return QIcon();
    }

    QWidget *getSettingPage() {
      _wgt = new QWidget();
      return _wgt;
    }

    void createWidgets() {}

    void createActions() {}

    void createConnectors() {}
};

#endif // BOOTMOCK_H
