#include "addroledialog.h"
#include "ui_addroledialog.h"
#include <QRegExp>
#include <QRegExpValidator>

#include <library/orm/db/QDjangoQuerySet.h>
#include "models/promissionqdjangomodel.h"

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

    ui->promissionBox->clear();

    QSqlDatabase m_db = QSqlDatabase::database("autorization");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "autorization");
    }

    QString path = QString("%1/%2")
            .arg(QCoreApplication::applicationDirPath()).arg("__autorization");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);
    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<Promission>();
        QDjango::createTables();

        QDjangoQuerySet<Promission> proms;
        ui->promissionBox->addItem("");
        QList<QVariantMap> propertyMaps = proms.values(QStringList() << "signature");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            ui->promissionBox->addItem(propertyMap["signature"].toString());
        }
    }

    m_db.close();
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

void AddRoleDialog::on_buttonBox_accepted()
{
    QSqlDatabase m_db = QSqlDatabase::database("autorization");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "autorization");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__autorization");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {
        QDjango::setDatabase(m_db);
        QDjango::registerModel<Role>();
        QDjango::createTables();
        QDjangoQuerySet<Role> roles;
        bool isFind = false;

        QList<QVariantMap> propertyMaps = roles.values(QStringList() << "name" << "promission");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["name"].toString() == ui->roleEdit->text()) {
                isFind = true;
            }
        }

        if (!isFind) {
            m_modelRoles->addRole(ui->roleEdit->text(), ui->promissionEdit->text());
            m_modelRoles->updateModel();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText(tr("Роль с таким названием уже существует!"));
            msgBox.exec();
        }
    }

    m_db.close();

}
