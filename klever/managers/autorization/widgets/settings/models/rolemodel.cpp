#include "rolemodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>



RoleModel::RoleModel()
{

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("autoriz");
    m_db.open();

    QDjango::setDatabase(m_db);
    QDjango::registerModel<Role>();

    QDjango::createTables();

}

RoleModel::~RoleModel()
{
    m_db.close();
}

QStringList RoleModel::selectAllRoles()
{
    QDjangoQuerySet<Role> roles;
    QStringList tmp;

    tmp.clear();

    QList<QVariantMap> propertyMaps = roles.values(QStringList() << "name" << "promission");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        tmp.append(propertyMap["name"].toString());
    }

    return tmp;
}

void RoleModel::addRole(QString name, QString promission) {
    Role *role = new Role;
    role->setName(name);
    role->setPromission(promission);
    role->save();
}

void RoleModel::updateModel()
{
    setStringList(selectAllRoles());
}

void RoleModel::deleteRole(const QModelIndex &index)
{
    QStringList rolesList;
    rolesList.clear();

    QString name = data(index, Qt::DisplayRole).toString();
    removeRows(0, 1, index);

    QDjangoQuerySet<Role> roles;
    roles = roles.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));
    roles.remove();


    QDjangoQuerySet<Group> groups;
    groups = groups.filter(QDjangoWhere("role", QDjangoWhere::Equals, name));

    Group group;
    for (int i = 0; i < groups.size(); ++i) {
      if (groups.at(i, &group)) {
        group.setRole(QString(""));
        group.save();
      }
    }

}
