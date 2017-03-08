#include "newrequirementdialog.h"
#include "ui_newrequirementdialog.h"
#include "../../../_shared/db/models/requirementelement.h"
#include "../../../_shared/db/models/architectelement.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QDir>
#include <QClipboard>

#include <frameWork/base.h>
#include <library/orm/db/QDjangoQuerySet.h>


NewRequirementDialog::NewRequirementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRequirementDialog)
{
    ui->setupUi(this);
}

NewRequirementDialog::~NewRequirementDialog()
{
    delete ui;
}

/*
 *
 */
void NewRequirementDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<ArchitectElement>();
        QDjango::createTables();
        ui->requirementComboBox->setCurrentText(
                    Core::Base::instance().getParameterValue(QString("RTYPE"),QString("")));

        ui->componentBox->clear();
        ArchitectElement ae;
        QDjangoQuerySet<ArchitectElement> someArchitectElements;

        // Поиск системы
        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {

                if (ae.type() == "Компонент") {
                    ui->componentBox->addItem(ae.article());
                }
            }
        }
    }

    m_db.close();
}

void NewRequirementDialog::on_componentBox_currentTextChanged(const QString &arg1)
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<ArchitectElement>();
        QDjango::createTables();
        ui->moduleBox->clear();

        ArchitectElement ae;
        QDjangoQuerySet<ArchitectElement> someArchitectElements;

        // Поиск системы
        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {
                if (ae.type() == "Модуль") {
                    if (ae.parentElementArticle()== arg1) {
                        ui->moduleBox->addItem(ae.article());
                    }
                }
            }
        }
    }

    m_db.close();
}

/*
 *
 */
void NewRequirementDialog::on_buttonBox_accepted()
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<RequirementElement>();
        QDjango::createTables();
        QDjangoQuerySet<RequirementElement> someRequirementElements;

        QVector<bool> identify(MAX_REQUIREMENT_COUNT, false);

        int rid = -1;

        RequirementElement m_re;
        for (int i = 0; i < someRequirementElements.size(); ++i) {
            if (someRequirementElements.at(i, &m_re)) {
                if (m_re.rtype() == ui->requirementComboBox->currentText()) {
                    identify[m_re.identificator()] = true;
                }
            }
        }

        for (int i = 0; i < identify.size(); i++) {
            if (!identify.value(i, false)) {
                rid = i;
                break;
            }
        }

        if (rid == -1) {
            rid = identify.size() + 1;
        }

        RequirementElement re;
        re.setRType(ui->requirementComboBox->currentText());
        re.setName(ui->nameEdit->text());
        re.setComponent(ui->componentBox->currentText());
        re.setModule(ui->moduleBox->currentText());
        re.setIdentificator(rid);

        re.save();
    }

    m_db.close();
}


