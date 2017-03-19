#include "editroledialog.h"
#include "ui_editroledialog.h"
#include <QRegExp>
#include <QRegExpValidator>

#include <library/orm/db/QDjangoQuerySet.h>
#include "models/promissionqdjangomodel.h"
#include "models/roleqdjangomodel.h"

EditRoleDialog::EditRoleDialog(QWidget *parent, QString name) :
  QDialog(parent),
  ui(new Ui::EditRoleDialog)
{
  ui->setupUi(this);

  QRegExp rx("[A-Za-z0-9]+");
  QValidator *validator = new QRegExpValidator(rx, this);

  ui->roleEdit->setValidator(validator);


  if (!name.isEmpty()) {

      QDjangoQuerySet<Promission> proms;
      ui->promissionBox->addItem("");
      QList<QVariantMap> propertyMaps = proms.values(QStringList() << "signature");
      foreach (const QVariantMap &propertyMap, propertyMaps) {
        ui->promissionBox->addItem(propertyMap["signature"].toString());
      }

      QDjangoQuerySet<Role> roles;

      propertyMaps = roles.values(QStringList() << "name");
      foreach (const QVariantMap &propertyMap, propertyMaps) {
          if (propertyMap["name"].toString() == name) {
              m_name = propertyMap["name"].toString();
              m_promission = propertyMap["promission"].toString();
          }
      }

      ui->roleEdit->setText(m_name);
      ui->promissionEdit->setText(m_promission);

      ui->addButton->setEnabled(true);

      if (ui->roleEdit->text().isEmpty()) {
          ui->deleteButton->setEnabled(false);
      }
      else {
          ui->deleteButton->setEnabled(true);
      }
  }
}

EditRoleDialog::~EditRoleDialog()
{
  delete ui;
}

void EditRoleDialog::on_addButton_clicked()
{
  QString txt = ui->promissionEdit->text();

  if (txt.isEmpty()) {
      txt = ui->promissionBox->currentText();
  }
  else {
    QStringList promsList;
    promsList = txt.split(",");

    bool isFind = false;

    foreach (QString t, promsList) {
      if (t == ui->promissionBox->currentText()) {
        isFind = true;
        break;
      }
    }
    if (!isFind) {
        txt += QString("%1%2").arg(",").arg(ui->promissionBox->currentText());
    }
  }

  ui->promissionEdit->setText(txt);

}


QString EditRoleDialog::name() const
{
    return ui->roleEdit->text();
}

QString EditRoleDialog::promission() const
{
    return ui->promissionEdit->text();
}

void EditRoleDialog::on_deleteButton_clicked()
{
    QString txt = ui->promissionEdit->text();

    if (!txt.isEmpty()) {
      QStringList promsList;
      promsList = txt.split(",");
      txt = "";

      foreach (QString t, promsList) {
        if (t != ui->promissionBox->currentText()) {
            if  (txt.isEmpty()) {
                txt += QString("%1").arg(t);
            }
            else {
                txt += QString("%1%2").arg(",").arg(t);
            }
        }
      }
    }

    ui->promissionEdit->setText(txt);
}
