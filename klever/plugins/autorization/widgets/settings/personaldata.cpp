#include "personaldata.h"
#include "ui_personaldata.h"

#include "addgroupdialog.h"
#include "editgroupdialog.h"

#include "adduserdialog.h"
#include "edituserdialog.h"

#include "addpromissiondialog.h"

#include "addroledialog.h"
#include "editroledialog.h"

#include <library/orm/db/QDjangoQuerySet.h>

#include "models/groupqdjangomodel.h"
#include "models/userqdjangomodel.h"
#include "models/promissionqdjangomodel.h"
#include "models/roleqdjangomodel.h"


#include <QMessageBox>
#include <QDebug>


PersonalData::PersonalData(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PersonalData)
{
    ui->setupUi(this);

    // Создание модели групп
    QStringList headers;
    headers << tr("Группа")<< tr("Описание");

    m_modelGroups = new GroupModel(headers);
    ui->groupsView->setModel(m_modelGroups);
    ui->groupsView->setColumnWidth(0, 150);
    ui->groupsView->setSelectionMode(QAbstractItemView::SingleSelection);

    // Создание модели пользователей
    m_modelUsers = new UserModel();
    m_modelUsers->setStringList(m_modelUsers->selectAllUsers());
    ui->usersView->setModel(m_modelUsers);

    // Создание модели разрешений
    m_modelPromissions = new PromissionModel();
    m_modelPromissions->setStringList(m_modelPromissions->selectAllPromission());
    ui->promissionsView->setModel(m_modelPromissions);

    // Создание модели ролей
    m_modelRoles = new RoleModel();
    m_modelRoles->setStringList(m_modelRoles->selectAllRoles());
    ui->rolesView->setModel(m_modelRoles);

}

PersonalData::~PersonalData()
{
    delete ui;
}

void PersonalData::on_addUserButton_clicked()
{
    AddUserDialog *dial = new AddUserDialog();

    if ( dial->exec() == QDialog::Accepted ) {
      QDjangoQuerySet<User> users;
      bool isFind = false;

      QList<QVariantMap> propertyMaps = users.values(QStringList() << "username");
      foreach (const QVariantMap &propertyMap, propertyMaps) {
          if (propertyMap["username"].toString() == dial->username()) {
              isFind = true;
          }
      }

      if (!isFind) {
          m_modelUsers->addUser(dial->username(), dial->password(), dial->group());
          m_modelUsers->updateModel();
      }
      else {
          QMessageBox msgBox;
          msgBox.setText(tr("Пользователь с таким названием уже существует!"));
          msgBox.exec();
      }
    }

    delete dial;

}

void PersonalData::on_addGroupButton_clicked()
{
    AddGroupDialog *dial = new AddGroupDialog();

    if ( dial->exec() == QDialog::Accepted ) {

        QDjangoQuerySet<Group> groups;
        bool isFind = false;

        QList<QVariantMap> propertyMaps = groups.values(QStringList() << "name" << "role" << "parent" << "description" << "id");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["name"].toString() == dial->name()) {
                isFind = true;
            }
        }

        if (!isFind) {
            m_modelGroups->addGroup(dial->name(), dial->parent(), dial->role(), dial->description());
            m_modelGroups->updateModel();
            ui->groupsView->expandAll();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText(tr("Группа с таким названием уже существует!"));
            msgBox.exec();
        }
    }

    delete dial;

}

void PersonalData::on_editGroupButton_clicked()
{
    QString  name = m_modelGroups->getName(ui->groupsView->currentIndex()).toString();

    EditGroupDialog *dial = new EditGroupDialog(NULL, name);

    QModelIndex tmp = ui->groupsView->currentIndex();

    if (!name.isEmpty()) {
        if ( dial->exec() == QDialog::Accepted ) {
            m_modelGroups->deleteGroup(tmp);
            m_modelGroups->addGroup(dial->name(), dial->parent(), dial->role(), dial->description());
            m_modelGroups->updateModel();
            ui->groupsView->expandAll();
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(QString("Название группы: %1!").arg(name));
        msgBox.exec();
    }

    delete dial;
}

void PersonalData::on_deleteGroupButton_clicked()
{
    m_modelGroups->deleteRecursiveGroup(ui->groupsView->currentIndex());
    m_modelGroups->updateModel();
    ui->groupsView->expandAll();
}

void PersonalData::on_editUserButton_clicked()
{
    EditUserDialog *dial = new EditUserDialog(NULL,
          m_modelUsers->data(ui->usersView->currentIndex(), Qt::DisplayRole).toString());

     QModelIndex tmp = ui->usersView->currentIndex();

    if ( dial->exec() == QDialog::Accepted ) {

        m_modelUsers->deleteUser(tmp);

        QDjangoQuerySet<User> users;
        bool isFind = false;

        QList<QVariantMap> propertyMaps = users.values(QStringList() << "username");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["username"].toString() == dial->username()) {
                isFind = true;
            }
        }

        if (!isFind) {
            m_modelUsers->addUser(dial->username(), dial->password(), dial->group());
            m_modelUsers->updateModel();
        } else {
            QMessageBox msgBox;
            msgBox.setText(tr("Пользователь с таким названием уже существует!"));
            msgBox.exec();
        }
    }

    delete dial;
}

void PersonalData::on_deleteUserButton_clicked()
{
    m_modelUsers->deleteUser(ui->usersView->currentIndex());
    m_modelUsers->updateModel();
}

void PersonalData::on_addPromissionButton_clicked()
{
    AddPromissionDialog *dial = new AddPromissionDialog();

    dial->setModelPromissions(m_modelPromissions);
    dial->exec();

    dial->deleteLater();
}

void PersonalData::on_deletePromissionButton_clicked()
{
    m_modelPromissions->deletePromission(ui->promissionsView->currentIndex());
    m_modelPromissions->updateModel();
}

void PersonalData::on_addRoleButton_clicked()
{
    AddRoleDialog *dial = new AddRoleDialog();

    dial->setModelRoles(m_modelRoles);
    dial->exec();

    dial->deleteLater();
}

void PersonalData::on_editRoleButton_clicked()
{

    QString oldRoleName = m_modelRoles->data(ui->rolesView->currentIndex(), Qt::DisplayRole).toString();

    EditRoleDialog *dial = new EditRoleDialog(NULL, oldRoleName);

    if ( dial->exec() == QDialog::Accepted ) {

        QDjangoQuerySet<Role> roles;

        roles = roles.filter(QDjangoWhere("name", QDjangoWhere::Equals, dial->name()));

        // Если подобных записей нет, то создаем...
        if (roles.size() == 0) {
            QDjangoQuerySet<Role> roles;
            Role role;
            roles = roles.filter(QDjangoWhere("name", QDjangoWhere::Equals, oldRoleName));
            roles.at(0, &role);
            role.setName(dial->name());
            role.setPromission(dial->promission());
            role.save();

            QDjangoQuerySet<Group> groups;
            groups = groups.filter(QDjangoWhere("role", QDjangoWhere::Equals, oldRoleName));

            Group group;
            for (int i = 0; i < groups.size(); ++i) {
              if (groups.at(i, &group)) {
                group.setRole(dial->name());
                group.save();
              }
            }

            m_modelRoles->updateModel();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText(tr("Роль с таким названием уже существует!"));
            msgBox.exec();
        }
    }

    delete dial;
}

void PersonalData::on_deleteRoleButton_clicked()
{
    m_modelRoles->deleteRole(ui->rolesView->currentIndex());
    m_modelRoles->updateModel();
}

void PersonalData::on_promissionsView_clicked(const QModelIndex &index)
{
//    QString name = m_modelPromissions->data(index, Qt::DisplayRole).toString();

//    QDjangoQuerySet<Promission> proms;
//    proms = proms.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));
//    // Если запись такая одна ...
//    if (proms.size() == 1) {
//         Promission prom;
//         proms.at(0, &prom);
//         ui->infoLabel->setText(QString("Сигнатура: %1 тип: %2").arg(prom.signature()).arg(prom.constant()));
//    }
//    else {
//      QMessageBox msgBox;
//      msgBox.setText(tr("Разрешений с подобным именем больше одного!"));
//      msgBox.exec();
//    }
}
