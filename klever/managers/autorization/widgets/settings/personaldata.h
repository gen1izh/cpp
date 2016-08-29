#ifndef PERSONALDATA_H
#define PERSONALDATA_H

#include <QWidget>
#include <QDebug>

#include "models/groupmodel.h"

namespace Ui {
class PersonalData;
}

class PersonalData : public QWidget
{
  Q_OBJECT

   GroupModel *m_model;

public:
  explicit PersonalData(QWidget *parent = 0);
  ~PersonalData();

private slots:
   void on_addUserButton_clicked();

   void on_addGroupButton_clicked();

   void on_editGroupButton_clicked();

   void on_deleteGroupButton_clicked();

private:
  Ui::PersonalData *ui;
};

#endif // PERSONALDATA_H
