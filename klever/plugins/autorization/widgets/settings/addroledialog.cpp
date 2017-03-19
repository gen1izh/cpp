#include "addroledialog.h"
#include "ui_addroledialog.h"
#include <QRegExp>
#include <QRegExpValidator>

#include <library/orm/db/QDjangoQuerySet.h>
#include "models/promissionqdjangomodel.h"
#include <frameWork/base.h>
#include <QMessageBox>
#include <library/message/messagelibrary.h>
#include <QtSql/QSqlDatabase>

RoleModel *AddRoleDialog::modelRoles() const
{
    return m_modelRoles;
}

void AddRoleDialog::setModelRoles(RoleModel *modelRoles)
{
    m_modelRoles = modelRoles;
}

AddRoleDialog::AddRoleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRoleDialog)
{

    ui->setupUi(this);
}

void AddRoleDialog::showEvent(QShowEvent *) {
    QRegExp rx("[A-Za-z0-9]+");
    QValidator *validator = new QRegExpValidator(rx, this);

    ui->roleEdit->setValidator(validator);

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Promission>();
    QDjango::createTables();

    // Заполнение раскрывающегося списка групп всеми возможными группами
    QDjangoQuerySet<Group> groups;
    ui->groupBox->addItem("");
    QList<QVariantMap> propertyMaps = groups.values(QStringList() << "name");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        ui->groupBox->addItem(propertyMap["name"].toString());
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

void AddRoleDialog::on_buttonBox_accepted()
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Role>();
    QDjango::createTables();
    QDjangoQuerySet<Role> roles;
    bool isFind = false;

    QList<QVariantMap> propertyMaps = roles.values(QStringList() << "name");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        if (propertyMap["name"].toString() == ui->roleEdit->text()) {
            isFind = true;
        }
    }

    if (!isFind) {
        m_modelRoles->addRole(ui->roleEdit->text());
        m_modelRoles->updateModel();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(tr("Роль с таким названием уже существует!"));
        msgBox.exec();
    }
}
