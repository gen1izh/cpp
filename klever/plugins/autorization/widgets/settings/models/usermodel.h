#ifndef USERMODEL_H
#define USERMODEL_H
#include <QStringListModel>
#include <QtSql/QSqlDatabase>

class UserModel : public QStringListModel
{

  QSqlDatabase m_db;

public:
  UserModel();
  ~UserModel();

  QStringList selectAllUsers();

  void addUser(QString username, QString password, QString group);

  void updateModel();

  void deleteUser(const QModelIndex &index);

  QString getUserPasswordByName(QString username);
};

#endif // USERMODEL_H
