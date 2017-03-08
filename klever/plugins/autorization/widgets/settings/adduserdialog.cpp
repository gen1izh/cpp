#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <library/orm/db/QDjangoQuerySet.h>
#include "models/userqdjangomodel.h"
#include "models/groupqdjangomodel.h"
#include <library/message/messagelibrary.h>

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
}


void AddUserDialog::showEvent(QShowEvent *) {

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

    m_db.close();
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
