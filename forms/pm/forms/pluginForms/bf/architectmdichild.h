#ifndef ARCHITECTMDICHILD_H
#define ARCHITECTMDICHILD_H

#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>

#include <frameWork/base.h>
#include <plugins/logger/logger.h>

class ArchitectMdiChild : public QWidget {

  Q_OBJECT

  signals:
    void setVisibleSignal(bool visible);

  public:
    void closeEvent(QCloseEvent *event);

    ArchitectMdiChild();
    ~ArchitectMdiChild();

};

#endif // ARCHITECTMDICHILD_H
