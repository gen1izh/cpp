#ifndef CONTROLPOWERMDICHILD_H
#define CONTROLPOWERMDICHILD_H

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QCloseEvent>
#include <QDebug>
#include <QToolBar>
#include <QAction>
#include <QMenu>


class ControlMdiChild : public QWidget {

  Q_OBJECT

  public:
    ControlMdiChild();
    ~ControlMdiChild();

    void closeEvent(QCloseEvent *event);

  signals:
    void setVisibleSignal(bool visible);

};

#endif // CONTROLPOWERMDICHILD_H
