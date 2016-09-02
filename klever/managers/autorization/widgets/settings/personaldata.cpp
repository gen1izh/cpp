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

}

void PersonalData::on_editGroupButton_clicked()
{
    EditGroupDialog *dial = new EditGroupDialog(NULL,
          m_modelGroups->data(ui->groupsView->currentIndex(), Qt::DisplayRole).toString());

     QModelIndex tmp = ui->groupsView->currentIndex();

    if ( dial->exec() == QDialog::Accepted ) {
      m_modelGroups->deleteGroup(tmp);
      m_modelGroups->addGroup(dial->name(), dial->parent(), dial->role(), dial->description());
      m_modelGroups->updateModel();
      ui->groupsView->expandAll();
    }

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
}

void PersonalData::on_deleteUserButton_clicked()
{
    m_modelUsers->deleteUser(ui->usersView->currentIndex());
    m_modelUsers->updateModel();
}

void PersonalData::on_addPromissionButton_clicked()
{
    AddPromissionDialog *dial = new AddPromissionDialog();

    if ( dial->exec() == QDialog::Accepted ) {

        QDjangoQuerySet<Promission> proms;
        bool isFind = false;

        QList<QVariantMap> propertyMaps = proms.values(QStringList() << "name" << "signature" << "constant");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["signature"].toString() == dial->signature()) {
                isFind = true;
            }
        }

        if (!isFind) {
            m_modelPromissions->addPromission(dial->name(), dial->signature(), "");
            m_modelPromissions->updateModel();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText(tr("Разрешение с таким названием уже существует!"));
            msgBox.exec();
        }
    }
}

void PersonalData::on_deletePromissionButton_clicked()
{
    m_modelPromissions->deletePromission(ui->promissionsView->currentIndex());
    m_modelPromissions->updateModel();
}

void PersonalData::on_addRoleButton_clicked()
{
    AddRoleDialog *dial = new AddRoleDialog();

    if ( dial->exec() == QDialog::Accepted ) {
        QDjangoQuerySet<Role> proms;
        bool isFind = false;

        QList<QVariantMap> propertyMaps = proms.values(QStringList() << "name" << "promission");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["name"].toString() == dial->name()) {
                isFind = true;
            }
        }

        if (!isFind) {
            m_modelRoles->addRole(dial->name(), dial->promissions());
            m_modelRoles->updateModel();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText(tr("Роль с таким названием уже существует!"));
            msgBox.exec();
        }
    }
}

void PersonalData::on_editRoleButton_clicked()
{
  EditRoleDialog *dial = new EditRoleDialog(NULL,
        m_modelRoles->data(ui->rolesView->currentIndex(), Qt::DisplayRole).toString());

   QModelIndex tmp = ui->rolesView->currentIndex();

  if ( dial->exec() == QDialog::Accepted ) {

      m_modelRoles->deleteRole(tmp);

      QDjangoQuerySet<Role> roles;
      bool isFind = false;

      QList<QVariantMap> propertyMaps = roles.values(QStringList() << "name");
      foreach (const QVariantMap &propertyMap, propertyMaps) {
          if (propertyMap["name"].toString() == dial->name()) {
              isFind = true;
          }
      }

      if (!isFind) {
          m_modelRoles->addRole(dial->name(), dial->promission());
          m_modelRoles->updateModel();
      } else {
          QMessageBox msgBox;
          msgBox.setText(tr("Роль с таким названием уже существует!"));
          msgBox.exec();
      }
  }
}

void PersonalData::on_deleteRoleButton_clicked()
{
    m_modelRoles->deleteRole(ui->rolesView->currentIndex());
    m_modelRoles->updateModel();
}
