#ifndef autorization_SETTINGS_H
#define autorization_SETTINGS_H

#include <QWidget>
#include "personaldata.h"

class autorizationSettings : public QWidget
{
  Q_OBJECT

  void createConnectors();

public:
  explicit autorizationSettings(QWidget *parent = 0);

  PersonalData *d;

signals:

};

#endif // autorization_SETTINGS_H

