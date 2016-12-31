#include "addroledialog.h"
#include "ui_addroledialog.h"
#include <QRegExp>
#include <QRegExpValidator>

#include <library/orm/db/QDjangoQuerySet.h>
#include "models/promissionqdjangomodel.h"

AddRoleDialog::AddRoleDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddRoleDialog)
{

    ui->setupUi(this);
    QRegExp rx("[A-Za-z0-9]+");
    QValidator *validator = new QRegExpValidator(rx, this);

    ui->roleEdit->setValidator(validator);

    QDjangoQuerySet<Promission> proms;
    ui->promissionBox->addItem("");
    QList<QVariantMap> propertyMaps = proms.values(QStringList() << "signature");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
      ui->promissionBox->addItem(propertyMap["signature"].toString());
    }


}

AddRoleDialog::~AddRoleDialog()
{
    delete ui;
}

QString AddRoleDialog::name() const
{
    return ui->roleEdit->text();
}

QString AddRoleDialog::promissions() const
{
    return ui->promissionEdit->text();
}

void AddRoleDialog::on_addButton_clicked()
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
