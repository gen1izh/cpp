#include "editgroupdialog.h"
#include "ui_editgroupdialog.h"

#include <library/orm/db/QDjangoQuerySet.h>
#include "models/groupqdjangomodel.h"

EditGroupDialog::EditGroupDialog(QWidget *parent, QString groupName) :
  QDialog(parent),
  ui(new Ui::EditGroupDialog)
{
    ui->setupUi(this);

    if (!groupName.isEmpty()) {
        QDjangoQuerySet<Group> groups;

        ui->parentBox->clear();
        ui->parentBox->addItem("");

        QList<QVariantMap> propertyMaps = groups.values(QStringList() << "name" << "role" << "parent" << "description" << "id");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["name"].toString() == groupName) {
                m_role = propertyMap["role"].toString();
                m_description = propertyMap["description"].toString();
                m_name = propertyMap["name"].toString();
                m_parent = propertyMap["parent"].toString();
            }
            ui->parentBox->addItem(propertyMap["name"].toString());
        }

        ui->parentBox->setCurrentText(m_parent);
        ui->descriptionEdit->setText(m_description);
        ui->groupEdit->setText(m_name);
        ui->rolesBox->setCurrentText(m_role);
    }
}

EditGroupDialog::~EditGroupDialog()
{
  delete ui;
}

QString EditGroupDialog::name() const
{
    return ui->groupEdit->text();
}

QString EditGroupDialog::parent() const
{
    return ui->parentBox->currentText();
}

QString EditGroupDialog::role() const
{
    return ui->rolesBox->currentText();
}

QString EditGroupDialog::description() const
{
    return ui->descriptionEdit->toPlainText();
}





