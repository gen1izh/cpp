#ifndef LOGGERSWATCHERMDICHILD_H
#define LOGGERSWATCHERMDICHILD_H

#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>

#include <frameWork/base.h>
#include <plugins/logger/cveLogger.h>

class LoggersWatcherMdiChild : public QWidget {

  Q_OBJECT

  signals:
    void setVisibleSignal(bool visible);

  public:
    void closeEvent(QCloseEvent *event);

    LoggersWatcherMdiChild();
    ~LoggersWatcherMdiChild();

};

#endif // LOGGERSWATCHERMDICHILD_H
