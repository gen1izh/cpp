#ifndef LOGGERMOCK_H
#define LOGGERMOCK_H

#include <interfaces/iloggermanager.h>
#include <QDebug>

class LoggerMock : public ILoggerManager
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
           QString        txt,
           MessagesTypes  type,
           LoggersTypes   loggertype = SYSTEM_LOG) {

    Q_UNUSED(ptr)
    Q_UNUSED(txt)
    Q_UNUSED(loggertype)

    if (type == MESSAGE_ERROR) {
      qDebug().noquote() << "[error] " << txt;
    }
    else if (type == MESSAGE_WARNING) {
      qDebug().noquote() << "[warning] " << txt;
    }
    else {
      qDebug().noquote() << "[info] " << txt;
    }

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

#endif // LOGGERMOCK_H
