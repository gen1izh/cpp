#ifndef USERMODEL_H
#define USERMODEL_H
#include <QStringListModel>
#include <QtSql/QSqlDatabase>
#include "groupqdjangomodel.h"
#include "roleqdjangomodel.h"

class UserModel : public QStringListModel
{

public:
  UserModel();
  ~UserModel();

  QStringList selectAllUsers();

  void addUser(QString username, QString password, Group *group);

  void updateModel();

  void deleteUser(const QModelIndex &index);

  QString getUserPasswordByName(QString username);
};

#endif // USERMODEL_H
