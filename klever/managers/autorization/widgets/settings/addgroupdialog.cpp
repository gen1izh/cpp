#include "addgroupdialog.h"
#include "ui_addgroupdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <library/orm/db/QDjangoQuerySet.h>

AddGroupDialog::AddGroupDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::addGroupDialog)
{
    ui->setupUi(this);

    QRegExp rx("^(\\w+\\s+)$");
    QValidator *validator = new QRegExpValidator(rx, this);

    ui->groupEdit->setValidator(validator);

    // Заполнение раскрывающегося списка групп всеми возможными группами
    ui->parentBox->clear();
    QDjangoQuerySet<Group> groups;
    ui->parentBox->addItem("");
    QList<QVariantMap> propertyMaps = groups.values(QStringList() << "name" << "role"<< "description" << "parent");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
      ui->parentBox->addItem(propertyMap["name"].toString());
    }

    // Заполнение раскрывающегося списка ролей всеми возможными ролями
    ui->rolesBox->clear();
    QDjangoQuerySet<Role> roles;
    ui->rolesBox->addItem("");
    propertyMaps = roles.values(QStringList() << "name");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
      ui->rolesBox->addItem(propertyMap["name"].toString());
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
//    Role *r;

//    QDjangoQuerySet<Role> roles;

//    // Проход по всем совпадениям
//    foreach (const Role &role, roles) {
//      if (role.name() == ui->rolesBox->currentText()) {
//        r = const_cast<Role *>(&role);
//      }
//    }

//    return r;

  return ui->rolesBox->currentText();
}

QString AddGroupDialog::description() const
{
    return ui->descriptionEdit->toPlainText();
}
