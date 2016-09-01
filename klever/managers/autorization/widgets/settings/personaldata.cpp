#include "personaldata.h"
#include "ui_personaldata.h"

#include "addgroupdialog.h"
#include "editgroupdialog.h"

#include "adduserdialog.h"
#include "edituserdialog.h"

#include <library/orm/db/QDjangoQuerySet.h>
#include "models/groupqdjangomodel.h"

#include "models/userqdjangomodel.h"

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
