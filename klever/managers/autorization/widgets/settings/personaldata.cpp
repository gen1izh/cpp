#include "personaldata.h"
#include "ui_personaldata.h"

#include "addgroupdialog.h"
#include "editgroupdialog.h"

#include <library/orm/db/QDjangoQuerySet.h>
#include "models/groupqdjangomodel.h"

#include <QMessageBox>


PersonalData::PersonalData(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PersonalData)
{
  ui->setupUi(this);

  QStringList headers;
  headers << tr("Группа")<< tr("Описание");

  m_model = new GroupModel(headers);
  ui->groupsView->setModel(m_model);
  ui->groupsView->setColumnWidth(0, 150);
  ui->groupsView->setSelectionMode(QAbstractItemView::SingleSelection);

}

PersonalData::~PersonalData()
{
  delete ui;
}

void PersonalData::on_addUserButton_clicked()
{

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
            m_model->addGroup(dial->name(), dial->parent(), dial->role(), dial->description());
            m_model->updateModel();
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
          m_model->data(ui->groupsView->currentIndex(), Qt::DisplayRole).toString());

     QModelIndex tmp = ui->groupsView->currentIndex();

    if ( dial->exec() == QDialog::Accepted ) {
      m_model->deleteGroup(tmp);
      m_model->addGroup(dial->name(), dial->parent(), dial->role(), dial->description());
      m_model->updateModel();
      ui->groupsView->expandAll();
    }

}

void PersonalData::on_deleteGroupButton_clicked()
{
  m_model->deleteRecursiveGroup(ui->groupsView->currentIndex());
  m_model->updateModel();
  ui->groupsView->expandAll();
}
