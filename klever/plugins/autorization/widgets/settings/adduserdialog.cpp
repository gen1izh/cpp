#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <library/orm/db/QDjangoQuerySet.h>
#include <frameWork/base.h>
#include <library/message/messagelibrary.h>

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
}


void AddUserDialog::showEvent(QShowEvent *) {
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<User>();
    QDjango::createTables();
    QRegExp rx("^(\\w+\\s+)$");
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

Group *AddUserDialog::group() const
{
    QDjangoQuerySet<Group> groups;
    Group *gr;
    for (int i = 0; i < groups.size(); ++i) {
        if (groups.at(i, gr)) {
            if (ui->groupsEdit->text() == gr->name()) {
                return gr;
            }
        }
    }
    return NULL;
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
