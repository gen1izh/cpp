#ifndef LOGGERMOCK_H
#define LOGGERMOCK_H

#include <interfaces/iloggermanager.h>
#include <QDebug>

class LoggerMock : public ILoggerPlugin
{

  QWidget *_wgt;

public:
  LoggerMock();


  /*!
   * \brief Функция журналирования сообщения
   * \param[in] ptr - указатель на объект источник сообщения
   * \param[in] txt - текст сообщения
   * \param[in] type - тип сообщения
   * \param[in] loggertype - тип журнала
   */
  void log(QObject       *ptr,
           const QString &datatime,
           const QString &txt,
           MessagesTypes  type) {

    if (type == MESSAGE_ERROR) {
      qDebug().noquote() << "[error] " << ptr->objectName()
                         << " " << datatime << " "  << txt;
    }
    else if (type == MESSAGE_WARNING) {
      qDebug().noquote() << "[warning] " << ptr->objectName()
                         << " " << datatime << " "  << txt;
    }
    else {
      qDebug().noquote() << "[information] " << ptr->objectName()
                         << " " << datatime << " "  << txt;
    }

  }

  QIcon settingIcon() {
    return QIcon();
  }

  QWidget *settingPage() {
    _wgt = new QWidget();
    return _wgt;
  }

  void createWidgets() {}

  void createActions() {}

  void createConnectors() {}
};

#endif // LOGGERMOCK_H
