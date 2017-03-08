#include "termsdialog.h"
#include "ui_termsdialog.h"

#include <library/orm/db/QDjangoQuerySet.h>
#include "../../../_shared/db/models/termselement.h"

#include <QScopedPointer>
#include <QDebug>
#include <QMessageBox>

#include <QtAlgorithms>
#include <library/message/messagelibrary.h>

TermsDialog::TermsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TermsDialog)
{
    ui->setupUi(this);

    for (int i = 0; i < ui->termsTable->rowCount(); i++) {
        for (int j = 0; j < ui->termsTable->columnCount(); j++) {
            QTableWidgetItem *_item = new QTableWidgetItem();
            ui->termsTable->setItem(i, j, _item);
        }
    }

    ui->termsTable->setColumnWidth(0, 100);
    ui->termsTable->setColumnWidth(1, 300);
}

/*
 *
 */
TermsDialog::~TermsDialog()
{
    for (int i = 0; i < ui->termsTable->rowCount(); i++) {
        for (int j = 0; j < ui->termsTable->columnCount(); j++) {
            delete ui->termsTable->item(i, j);
        }
    }

    delete ui;
}


/*
 *
 */
void TermsDialog::showEvent(QShowEvent *) {

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
        QDjango::registerModel<TermsElement>();
        QDjango::createTables();
        for (int i = 0; i < ui->termsTable->rowCount(); i++) {
            for (int j = 0; j < ui->termsTable->columnCount(); j++) {
                ui->termsTable->item(i, j)->setText("");
            }
        }

        QStringList keys;
        keys << "name";

        QDjangoQuerySet<TermsElement> someTermsElements;

        someTermsElements = someTermsElements.orderBy(keys);

        TermsElement m_re;
        int count = 0;
        for (int i = 0; i < someTermsElements.size(); ++i) {
            if (someTermsElements.at(i, &m_re)) {
                ui->termsTable->item(count, 0)->setText(m_re.name());
                ui->termsTable->item(count, 1)->setText(m_re.description());
                count++;
            }
        }
    }

    m_db.close();

}

void TermsDialog::on_buttonBox_accepted()
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
        QDjango::registerModel<TermsElement>();
        QDjango::createTables();
        QDjangoQuerySet<TermsElement> someTermsElements;

        someTermsElements.remove();

        for (int i = 0; i < ui->termsTable->rowCount(); i++ ) {
            if ((ui->termsTable->item(i, 0)!=NULL) &&
                    (ui->termsTable->item(i, 1)!=NULL)) {

                if ((!ui->termsTable->item(i, 0)->text().isEmpty()) &&
                    (!ui->termsTable->item(i, 1)->text().isEmpty())) {
                    TermsElement re;
                    re.setName(ui->termsTable->item(i, 0)->text().trimmed());
                    re.setDescription(ui->termsTable->item(i, 1)->text().trimmed());
                    re.save();
                }
            }
        }
    }

    m_db.close();
}

void TermsDialog::on_termsTable_cellClicked(int row, int column)
{
    ui->nameEdit->setText(ui->termsTable->item(row,0)->text());
    ui->descriptionEdit->setText(ui->termsTable->item(row,1)->text());
}

void TermsDialog::on_checkDuplicatesButton_clicked()
{
    QString tmp;
    tmp.clear();

    for (int i = 0; i < ui->termsTable->rowCount(); i++ ) {
        for (int j = i+1; j < ui->termsTable->rowCount()-1; j++ ) {
            if ((!ui->termsTable->item(i, 0)->text().isEmpty()) &&
                    (!ui->termsTable->item(i, 0)->text().isEmpty())){
                if (ui->termsTable->item(i, 0)->text() == ui->termsTable->item(j, 0)->text()) {
                    tmp += ui->termsTable->item(i, 0)->text();
                    tmp += " ";
                }
            }
        }
    }
    if (!tmp.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText(QString("Термины повторяются: %1 ").arg(tmp));
        msgBox.exec();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(QString("Термины не повторяются."));
        msgBox.exec();
    }
}


bool TermsDialog::caseInsensitiveLessThan(Term t1, Term t2)
{
    return t1.name().toLower() < t2.name().toLower();
}

QString Term::description() const
{
    return m_description;
}

void Term::setDescription(const QString &description)
{
    m_description = description;
}

QString Term::name() const
{
    return m_name;
}

void Term::setName(const QString &name)
{
    m_name = name;
}
