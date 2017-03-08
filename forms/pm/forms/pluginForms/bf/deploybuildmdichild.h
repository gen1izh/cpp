#ifndef DEPLOYBUILDMDICHILD_H
#define DEPLOYBUILDMDICHILD_H

#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>

#include <frameWork/base.h>
#include <plugins/logger/logger.h>

class DeployBuildMdiChild : public QWidget {

  Q_OBJECT

  signals:
    void setVisibleSignal(bool visible);

  public:
    void closeEvent(QCloseEvent *event);

    DeployBuildMdiChild();
    ~DeployBuildMdiChild();

};

#endif // DEPLOYBUILDMDICHILD_H
