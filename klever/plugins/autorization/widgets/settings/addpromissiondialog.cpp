#include "addpromissiondialog.h"
#include "ui_addpromissiondialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <frameWork/base.h>
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>

#include <QMessageBox>
#include <library/message/messagelibrary.h>
#include <QtSql/QSqlDatabase>

PromissionModel *AddPromissionDialog::modelPromissions() const
{
    return m_modelPromissions;
}

void AddPromissionDialog::setModelPromissions(PromissionModel *modelPromissions)
{
    m_modelPromissions = modelPromissions;
}

AddPromissionDialog::AddPromissionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPromissionDialog)
{

    ui->setupUi(this);

    QRegExp rx0("^(\\w+\\s+)$");
    QValidator *validator0 = new QRegExpValidator(rx0, this);

    ui->promissionEdit->setValidator(validator0);

    QRegExp rx1("^([A-Z0-9]+)$");
    QValidator *validator1 = new QRegExpValidator(rx1, this);

    ui->signatureEdit->setValidator(validator1);
}

AddPromissionDialog::~AddPromissionDialog()
{
  delete ui;
}

QString AddPromissionDialog::name() const
{
    return ui->promissionEdit->text();
}

QString AddPromissionDialog::signature() const
{
    return ui->signatureEdit->text();
}

void AddPromissionDialog::on_buttonBox_accepted()
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Promission>();
    QDjango::createTables();

    QDjangoQuerySet<Promission> proms;

    bool isFind = false;

    QList<QVariantMap> propertyMaps = proms.values(QStringList() << "name" << "signature" << "constant");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        if (propertyMap["signature"].toString() == ui->signatureEdit->text()) {
            isFind = true;
        }
    }

    if (!isFind) {

        QDjangoQuerySet<Role> roles;
        Role role;
        for (int i = 0; i < roles.size(); ++i) {
          if (roles.at(i, &role)) {
              if (role.name() == ui->rolesBox->currentText()) {
                  m_modelPromissions->addPromission(ui->promissionEdit->text(),
                                                    ui->signatureEdit->text(), "",
                                                    &role);
                  m_modelPromissions->updateModel();
                  break;
              }
          }
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(tr("Разрешение с таким названием уже существует!"));
        msgBox.exec();
    }

}

void AddPromissionDialog::showEvent(QShowEvent *)
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Promission>();
    QDjango::createTables();

    QDjangoQuerySet<Role> roles;

    QList<QVariantMap> propertyMaps = roles.values(QStringList() << "name" );
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        ui->rolesBox->addItem(propertyMap["name"].toString());
    }
}
