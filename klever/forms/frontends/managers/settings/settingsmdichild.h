#ifndef SETTINGSMDICHILD_H
#define SETTINGSMDICHILD_H

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDebug>
#include <QMenu>
#include <QWidget>

#include <frameWork/base.h>

class SettingsMdiChild : public QWidget {
  Q_OBJECT
  public:
    SettingsMdiChild();
    ~SettingsMdiChild(){
    }
    void closeEvent(QCloseEvent *event);
  signals:
    void setVisibleSignal(bool visible);
};

#endif // SETTINGSMDICHILD_H
