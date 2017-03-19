#include "bf_documentsform.h"
#include "ui_bf_documentsform.h"
#include <frameWork/base.h>

#include <QMessageBox>
#include <QDateTime>

#include <library/orm/db/QDjangoQuerySet.h>
#include "../../../_shared/db/models/docelement.h"

#include "generators/documentgenerator.h"



BF_DocumentsForm::BF_DocumentsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BF_DocumentsForm)
{
    ui->setupUi(this);
    createDialogs();

    for (int i = 0; i < ui->documentsListWidget->count(); i++ ) {
        ui->documentsListWidget->item(i)->setFlags(Qt::ItemIsEditable
                                                   | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
}

BF_DocumentsForm::~BF_DocumentsForm()
{
    delete ui;
}

void BF_DocumentsForm::on_editButton_clicked()
{

    if (!ui->documentsListWidget->selectedItems().isEmpty()) {
        Core::Base::instance().setParameterValue("NAME",
                        ui->documentsListWidget->selectedItems().at(0)->text());
        Core::Base::instance().setParameterValue("DOCTYPE", "ДОКУМЕНТ");

    }
    else {
        Core::Base::instance().setParameterValue("NAME",
                        ui->documentTreeWidget->selectedItems().at(0)->text(0));
        if (!ui->documentTreeWidget->selectedItems().isEmpty()) {

            if (ui->documentTreeWidget->currentItem()->parent() != NULL) {
                if (ui->documentTreeWidget->currentItem()->parent()->text(0) == "Приложения") {
                   Core::Base::instance().setParameterValue("DOCTYPE", "ПРИЛОЖЕНИЕ");
                }
                if (ui->documentTreeWidget->currentItem()->parent()->text(0) == "Информация о ПО") {
                   Core::Base::instance().setParameterValue("DOCTYPE", "ДОПОЛНИТЕЛЬНО");
                }
            }
        }
    }

    emit openTexteditor();

}

/*
 * Создание диалоговых окон.
 */
void BF_DocumentsForm::createDialogs()
{
    m_termsDialog = new  TermsDialog();
    m_glossaryDialog = new GlossaryDialog();
}


void BF_DocumentsForm::showEvent(QShowEvent *event) {
    Q_UNUSED(event)

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<DocElement>();
    QDjango::createTables();
    QDjangoQuerySet<DocElement> someDocElements;

    QList<QTreeWidgetItem*> appendixItem;
    appendixItem = ui->documentTreeWidget->findItems("Приложения",
                                               Qt::MatchRecursive);

    DocElement de;
    for (int i = 0; i < someDocElements.size(); ++i) {
        if (someDocElements.at(i, &de)) {
            if (de.type() == QString("ПРИЛОЖЕНИЕ")) {
                QTreeWidgetItem *_t = new QTreeWidgetItem();
                _t->setText(0, de.name());
                appendixItem.at(0)->addChild(_t);
            }
        }
    }
}

/*
 *
 */
void BF_DocumentsForm::on_createAppendixButton_clicked()
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<DocElement>();
    QDjango::createTables();
    QDjangoQuerySet<DocElement> someDocElements;

    DocElement de;
    for (int i = 0; i < someDocElements.size(); ++i) {
        if (someDocElements.at(i, &de)) {
            if ((de.name() == ui->appendixNameEdit->text())&&
                (de.type() == QString("ПРИЛОЖЕНИЕ"))) {
                QMessageBox msgBox;
                 msgBox.setText("Элемент с именем " +  ui->appendixNameEdit->text() + " создан несколько раз!"\
                                "Должен быть только один элемент!");
                 msgBox.exec();
            return;
            }
        }
    }

    DocElement de2;
    de2.setType(QString("ПРИЛОЖЕНИЕ"));
    de2.setName(ui->appendixNameEdit->text());
    de2.save();

    QList<QTreeWidgetItem*> appendixItem;
    appendixItem = ui->documentTreeWidget->findItems("Приложения",
                                               Qt::MatchRecursive);

    if (!appendixItem.isEmpty()) {
        QTreeWidgetItem *_t = new QTreeWidgetItem();
        _t->setText(0, ui->appendixNameEdit->text());
        appendixItem.at(0)->addChild(_t);
    }
}

void BF_DocumentsForm::on_deleteAppendixButton_clicked()
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<DocElement>();
    QDjango::createTables();
    QDjangoQuerySet<DocElement> someDocElements;

    DocElement de;
    for (int i = 0; i < someDocElements.size(); ++i) {
        if (someDocElements.at(i, &de)) {
            if ((de.name() == ui->documentTreeWidget->currentItem()->text(0))&&
                (de.type() == QString("ПРИЛОЖЕНИЕ"))) {
            de.remove();

            QList<QTreeWidgetItem*> appendixItem;
            appendixItem = ui->documentTreeWidget->findItems("Приложения",
                                                       Qt::MatchRecursive);

            if (!appendixItem.isEmpty()) {
                appendixItem.at(0)->removeChild(ui->documentTreeWidget->currentItem());
            }

            return;
            }
        }
    }
}

void BF_DocumentsForm::on_terminButton_clicked()
{
    int result = m_termsDialog->exec();

    if (result == QDialog::Accepted) {

    }
}

void BF_DocumentsForm::on_glossaryButton_clicked()
{
    int result = m_glossaryDialog->exec();

    if (result == QDialog::Accepted) {

    }
}

void BF_DocumentsForm::on_generateDocumentsButton_clicked()
{
    DocumentGenerator doc;

    Library::LoggerApi::logInfo(this, QString("<b>Начало генерации отчета:</b> %1")
                                .arg(QDateTime::currentDateTime().toString("ddd MMMM d yy hh:mm:ss.zzz")));

    Library::LoggerApi::logInfo(this, QString("Путь до файла <a href='%1'>%1</a>").arg(doc.generate()));

    Library::LoggerApi::logInfo(this, QString("<b>Генерация отчета завершена:</b> %1")
                            .arg(QDateTime::currentDateTime().toString("ddd MMMM d yy hh:mm:ss.zzz")));
}

void BF_DocumentsForm::on_documentTreeWidget_doubleClicked(const QModelIndex &index)
{
    on_editButton_clicked();
}

void BF_DocumentsForm::on_addDocumentButton_clicked()
{
    ui->documentsListWidget->addItem("Новый документ");
    for (int i = 0; i < ui->documentsListWidget->count(); i++ ) {
        ui->documentsListWidget->item(i)->setFlags(Qt::ItemIsEditable
                                                   | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
}

void BF_DocumentsForm::on_deleteDocumentButton_clicked()
{
    ui->documentsListWidget->takeItem(ui->documentsListWidget->currentRow());
}

void BF_DocumentsForm::on_documentTreeWidget_clicked(const QModelIndex &index)
{
    ui->documentsListWidget->clearSelection();
}

void BF_DocumentsForm::on_documentsListWidget_clicked(const QModelIndex &index)
{
    ui->documentTreeWidget->clearSelection();
}
