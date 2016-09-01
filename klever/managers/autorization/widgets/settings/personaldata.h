#ifndef PERSONALDATA_H
#define PERSONALDATA_H

#include <QWidget>
#include <QDebug>

#include "models/usermodel.h"
#include "models/groupmodel.h"
#include "models/promissionmodel.h"

namespace Ui {
class PersonalData;
}

class PersonalData : public QWidget
{
  Q_OBJECT

   GroupModel       *m_modelGroups;
   UserModel        *m_modelUsers;
   PromissionModel  *m_modelPromissions;

public:
  explicit PersonalData(QWidget *parent = 0);
  ~PersonalData();

private slots:
   void on_addUserButton_clicked();

   void on_addGroupButton_clicked();

   void on_editGroupButton_clicked();

   void on_deleteGroupButton_clicked();

   void on_editUserButton_clicked();

   void on_deleteUserButton_clicked();

   void on_addPromissionButton_clicked();

   void on_deletePromissionButton_clicked();

private:
  Ui::PersonalData *ui;
};

#endif // PERSONALDATA_H
