#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <library/orm/db/QDjangoQuerySet.h>
#include "models/userqdjangomodel.h"
#include "models/groupqdjangomodel.h"

AddUserDialog::AddUserDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddUserDialog)
{
  ui->setupUi(this);

  QRegExp rx("[A-Za-z0-9]+");
  QValidator *validator = new QRegExpValidator(rx, this);

  ui->usernameEdit->setValidator(validator);

  ui->passwordEdit->setValidator(validator);

  QDjangoQuerySet<Group> groups;

  ui->groupBox->addItem("");

  QList<QVariantMap> propertyMaps = groups.values(QStringList() << "name");
  foreach (const QVariantMap &propertyMap, propertyMaps) {
      ui->groupBox->addItem(propertyMap["name"].toString());
  }

}

AddUserDialog::~AddUserDialog()
{
  delete ui;
}

QString AddUserDialog::username() const
{
    return ui->usernameEdit->text();
}

QString AddUserDialog::group() const
{
    return ui->groupsEdit->text();
}

QString AddUserDialog::password() const
{
    return ui->passwordEdit->text();
}

void AddUserDialog::on_addButton_clicked()
{
    ui->groupsEdit->setText( ui->groupBox->currentText() );
    ui->addButton->setEnabled(false);
}
