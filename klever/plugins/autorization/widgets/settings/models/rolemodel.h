#ifndef ROLE_MODEL_H
#define ROLE_MODEL_H
#include <QStringListModel>
#include <QtSql/QSqlDatabase>

#include "roleqdjangomodel.h"
#include "groupqdjangomodel.h"

class RoleModel : public QStringListModel
{

public:
  RoleModel();
  ~RoleModel();

  QStringList selectAllRoles();

  void addRole(QString name);

  void updateModel();

  void deleteRole(const QModelIndex &index);

};

#endif // ROLE_MODEL_H
