#include "edituserdialog.h"
#include "ui_edituserdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <library/orm/db/QDjangoQuerySet.h>
#include "models/userqdjangomodel.h"
#include "models/groupqdjangomodel.h"

EditUserDialog::EditUserDialog(QWidget *parent, QString username) :
  QDialog(parent),
  ui(new Ui::EditUserDialog)
{
    ui->setupUi(this);
}

void EditUserDialog::showEvent(QShowEvent *) {

    QRegExp rx("^(\\w+\\s+)$");
    QValidator *validator = new QRegExpValidator(rx, this);

    ui->usernameEdit->setValidator(validator);

    ui->passwordEdit->setValidator(validator);

    if (!username().isEmpty()) {

        QDjangoQuerySet<Group> groups;
        ui->groupBox->addItem("");

        QList<QVariantMap> propertyMaps = groups.values(QStringList() << "name");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            ui->groupBox->addItem(propertyMap["name"].toString());
        }


        QDjangoQuerySet<User> users;

        propertyMaps = users.values(QStringList() << "username" << "password" << "group");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["username"].toString() == username()) {
                m_username = propertyMap["username"].toString();
                m_password = propertyMap["password"].toString();
                m_group = propertyMap["group"].toString();
            }
        }

        ui->usernameEdit->setText(m_username);
        ui->passwordEdit->setText(m_password);
        ui->groupsEdit->setText(m_group);

        if (ui->groupsEdit->text().isEmpty()) {
            ui->addButton->setEnabled(true);
            ui->deleteButton->setEnabled(false);
        }
        else {
            ui->addButton->setEnabled(false);
            ui->deleteButton->setEnabled(true);
        }
    }
}


EditUserDialog::~EditUserDialog()
{
    delete ui;
}

QString EditUserDialog::username() const
{
    return ui->usernameEdit->text();
}

Group *EditUserDialog::group() const
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

QString EditUserDialog::password() const
{
    return ui->passwordEdit->text();
}

void EditUserDialog::on_addButton_clicked()
{
    ui->groupsEdit->setText( ui->groupBox->currentText() );
    ui->addButton->setEnabled(false);
    ui->deleteButton->setEnabled(true);
}

void EditUserDialog::on_deleteButton_clicked()
{
    ui->groupsEdit->setText("");
    ui->addButton->setEnabled(true);
    ui->deleteButton->setEnabled(false);
}
