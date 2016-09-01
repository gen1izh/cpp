#include "addgroupdialog.h"
#include "ui_addgroupdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <library/orm/db/QDjangoQuerySet.h>
#include "models/groupqdjangomodel.h"

AddGroupDialog::AddGroupDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::addGroupDialog)
{
    ui->setupUi(this);

    QRegExp rx("[A-Za-z0-9]+");
    QValidator *validator = new QRegExpValidator(rx, this);

    ui->groupEdit->setValidator(validator);

    ui->parentBox->clear();

    QDjangoQuerySet<Group> groups;

    ui->parentBox->addItem("");

    QList<QVariantMap> propertyMaps = groups.values(QStringList() << "name" << "role"<< "description" << "parent");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
      ui->parentBox->addItem(propertyMap["name"].toString());
    }

}

AddGroupDialog::~AddGroupDialog()
{
    delete ui;
}

QString AddGroupDialog::name() const
{
    return ui->groupEdit->text();
}

QString AddGroupDialog::parent() const
{
    return ui->parentBox->currentText();
}

QString AddGroupDialog::role() const
{
    return ui->rolesBox->currentText();
}

QString AddGroupDialog::description() const
{
    return ui->descriptionEdit->toPlainText();
}
