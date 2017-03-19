#include "rolemodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include <QDebug>
#include <QCoreApplication>
#include <library/message/messagelibrary.h>
#include <frameWork/base.h>

RoleModel::RoleModel()
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Role>();
    QDjango::createTables();

    QDjangoQuerySet<Group> groups;
    groups = groups.filter(QDjangoWhere("name", QDjangoWhere::Equals, "Administrators"));

    if (groups.count()==0) {
        messageLibrary msg;
        msg.createInfoMessage("Информация", "Группы администраторов нет, роль создать не могу!");
    }
    else {
        // Создаем роль по-умолчанию
        QDjangoQuerySet<Role> roles;
        roles = roles.filter(QDjangoWhere("name", QDjangoWhere::Equals, "Admin"));

        if (roles.count()==0) {
            Role _role;
            _role.setName("Admin");
            _role.setGroup(groups.at(0));
            _role.save();
        }
    }
}

RoleModel::~RoleModel(){}

QStringList RoleModel::selectAllRoles()
{
    QStringList tmp;
    tmp.clear();

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Role>();
    QDjango::createTables();
    QDjangoQuerySet<Role> roles;

    QList<QVariantMap> propertyMaps = roles.values(QStringList() << "name");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        tmp.append(propertyMap["name"].toString());
    }

    return tmp;
}

void RoleModel::addRole(QString name) {

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Role>();
    QDjango::createTables();
    Role *role = new Role;
    role->setName(name);
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

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Role>();
    QDjango::createTables();

    QDjangoQuerySet<Role> roles;
    roles = roles.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));
    roles.remove();

}
