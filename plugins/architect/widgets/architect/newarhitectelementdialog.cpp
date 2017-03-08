#include "newarhitectelementdialog.h"
#include "ui_newarhitectelementdialog.h"
#include <frameWork/base.h>

#include <library/orm/db/QDjangoQuerySet.h>

#include "../../../_shared/db/models/architectelement.h"

#include <QMessageBox>

NewArhitectElementDialog::NewArhitectElementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewArhitectElementDialog)
{
    ui->setupUi(this);
}

/*
 *
 */
NewArhitectElementDialog::~NewArhitectElementDialog()
{
    delete ui;
}

/*
 *
 */
void NewArhitectElementDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    ui->parentNameLabel->setText(
                Core::Base::instance().getParameterValue(QString("Architect_ParentName"), QString("")));
    ui->parentTypeLabel->setText(
                    Core::Base::instance().getParameterValue(QString("Architect_ParentSmallText"), QString("")));

    ui->archElementBox->clear();
    QString architectLevel = ui->parentTypeLabel->text().trimmed();

    if (architectLevel == "Система") {
        ui->archElementBox->addItem("Подсистема");
        ui->elementTypeLabel->setText("Подсистема");
    }
    else if (architectLevel == "Подсистема") {
        ui->archElementBox->addItem("Компонент");
        ui->elementTypeLabel->setText("Компонент");
    }
    else if (architectLevel == "Компонент") {
        ui->archElementBox->addItem("Модуль");
        ui->elementTypeLabel->setText("Модуль");
    }
}

/*
 *
 */
void NewArhitectElementDialog::on_buttonBox_accepted()
{
    Core::Base::instance().setParameterValue(QString("Arhitect_Name"), ui->nameEdit->text());
    Core::Base::instance().setParameterValue(QString("Arhitect_SmallName"), ui->smallTextEdit->text());
    Core::Base::instance().setParameterValue(QString("Arhitect_Type"), ui->elementTypeLabel->text());

    if (!addNewElement()) {
        reject();
    }

}


/*
 *
 */
int NewArhitectElementDialog::addNewElement()
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

        QDjangoQuerySet<ArchitectElement> someArchitectElements;
        someArchitectElements = someArchitectElements.filter(QDjangoWhere("article",
                                                                          QDjangoWhere::Equals,
                                                                          ui->smallTextEdit->text()));

        if (someArchitectElements.size()>0) {
            QMessageBox msgBox;
             msgBox.setText("Элемент с идентификатором " +  ui->smallTextEdit->text() + " уже есть!"\
                            "Должен быть только один элемент c идентификатором!");
             msgBox.exec();
             return false;
        }
        else {
            ArchitectElement ae;

            ae.setArticle(ui->smallTextEdit->text());
            ae.setName(ui->nameEdit->text());
            ae.setDescription(ui->descriptionArchitectEdit->toPlainText());
            ae.setType(ui->archElementBox->currentText().trimmed());
            ae.setParentElementType(ui->parentTypeLabel->text().trimmed());
            ae.setParentElementArticle(ui->parentNameLabel->text().trimmed());

            ae.save();
        }
    }

    m_db.close();

    return true;
}

/*
 *
 */
void NewArhitectElementDialog::on_checkButton_clicked()
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
        ArchitectElement ae;

        QDjangoQuerySet<ArchitectElement> someArchitectElements;


        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {
                QString text = ae.article();
                if (text==ui->smallTextEdit->text()) {
                     QMessageBox msgBox;
                     msgBox.setText("Элемент с идентификатором " +  ui->smallTextEdit->text() + " уже есть!"\
                                    "Должен быть только один элемент c идентификатором!");
                     msgBox.exec();
                     return;
                }
            }
        }

        QMessageBox msgBox;
        msgBox.setText("Идентификатор уникален, используйте!");
        msgBox.exec();

    }

    m_db.close();
}
