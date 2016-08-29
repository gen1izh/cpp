#ifndef SESSIONMANAGERSETTINGS_H
#define SESSIONMANAGERSETTINGS_H

#include <QWidget>

#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QListView>
#include <QCheckBox>

#include "rightslistmodel.h"

class SessionManagerSettings : public QWidget
{
  Q_OBJECT

  QLabel          *_roleNameLabel;
  QLabel          *_rightsLabel;
  QComboBox       *_roleNameCombo;
  QPushButton     *_acceptButton;
  QListView       *_rightsList;
  QCheckBox       *_lockAll;

  RightsListModel *_rightsListModel;

  void createConnectors();

  void initParam();
public:
  explicit SessionManagerSettings(QWidget *parent = 0);

signals:

public slots:
  void acceptButton();
  void setCurrentRole(const QString &text);
};

#endif // SESSIONMANAGERSETTINGS_H
