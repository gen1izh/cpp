#include "glossarydialog.h"
#include "ui_glossarydialog.h"

#include <library/orm/db/QDjangoQuerySet.h>
#include "../../../_shared/db/models/glossaryelement.h"
#include <frameWork/base.h>
#include <QScopedPointer>
#include <QDebug>
#include <QMessageBox>
#include <library/message/messagelibrary.h>

GlossaryDialog::GlossaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlossaryDialog)
{
    ui->setupUi(this);

    for (int i = 0; i < ui->glossaryTable->rowCount(); i++) {
        for (int j = 0; j < ui->glossaryTable->columnCount(); j++) {
            QTableWidgetItem *_item = new QTableWidgetItem();
            ui->glossaryTable->setItem(i, j, _item);
        }
    }

    ui->glossaryTable->setColumnWidth(0, 100);

    ui->glossaryTable->setColumnWidth(1, 300);
}

/*
 *
 */
GlossaryDialog::~GlossaryDialog()
{
    for (int i = 0; i < ui->glossaryTable->rowCount(); i++) {
        for (int j = 0; j < ui->glossaryTable->columnCount(); j++) {
            delete ui->glossaryTable->item(i, j);
        }
    }

    delete ui;
}


/*
 *
 */
void GlossaryDialog::showEvent(QShowEvent *) {

//    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
//    QDjango::registerModel<GlossaryElement>();
//    QDjango::createTables();

    for (int i = 0; i < ui->glossaryTable->rowCount(); i++) {
        for (int j = 0; j < ui->glossaryTable->columnCount(); j++) {
            ui->glossaryTable->item(i, j)->setText("");
        }
    }

    QStringList keys;
    keys << "name";
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjangoQuerySet<GlossaryElement> someGlossaryElements;
    someGlossaryElements = someGlossaryElements.orderBy(keys);

    GlossaryElement m_re;
    int count = 0;
    for (int i = 0; i < someGlossaryElements.size(); ++i) {
        if (someGlossaryElements.at(i, &m_re)) {
            ui->glossaryTable->item(count, 0)->setText(m_re.name());
            ui->glossaryTable->item(count, 1)->setText(m_re.description());
            count++;
        }
    }

}


void GlossaryDialog::on_buttonBox_accepted()
{
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjangoQuerySet<GlossaryElement> someGlossaryElements;

    someGlossaryElements.remove();

    for (int i = 0; i < ui->glossaryTable->rowCount(); i++ ) {
        if ((ui->glossaryTable->item(i, 0)!=NULL) &&
                (ui->glossaryTable->item(i, 1)!=NULL)) {

            if ((!ui->glossaryTable->item(i, 0)->text().isEmpty()) &&
                (!ui->glossaryTable->item(i, 1)->text().isEmpty())) {
                GlossaryElement re;
                re.setName(ui->glossaryTable->item(i, 0)->text().trimmed());
                re.setDescription(ui->glossaryTable->item(i, 1)->text().trimmed());
                re.save();
            }
        }

    }
}

void GlossaryDialog::on_glossaryTable_cellClicked(int row, int column)
{
    ui->nameEdit->setText(ui->glossaryTable->item(row,0)->text());
    ui->descriptionEdit->setText(ui->glossaryTable->item(row,1)->text());
}

void GlossaryDialog::on_checkDublicatesButton_clicked()
{
    QString tmp;
    tmp.clear();

    for (int i = 0; i < ui->glossaryTable->rowCount(); i++ ) {
        for (int j = i+1; j < ui->glossaryTable->rowCount()-1; j++ ) {
            if ((!ui->glossaryTable->item(i, 0)->text().isEmpty()) &&
                    (!ui->glossaryTable->item(i, 0)->text().isEmpty())){
                if (ui->glossaryTable->item(i, 0)->text() == ui->glossaryTable->item(j, 0)->text()) {
                    tmp += ui->glossaryTable->item(i, 0)->text();
                    tmp += " ";
                }
            }
        }
    }
    if (!tmp.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText(QString("Определения повторяются: %1 ").arg(tmp));
        msgBox.exec();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(QString("Определения не повторяются."));
        msgBox.exec();
    }
}
