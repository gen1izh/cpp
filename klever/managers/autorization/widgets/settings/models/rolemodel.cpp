#include "rolemodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>

#include "roleqdjangomodel.h"

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
    QDjangoQuerySet<Role> someRoles;
    someRoles = roles.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));
    someRoles.remove();

    //TODO: Нужно найти группы у которых роль = name и очистить поле роли у них
}
