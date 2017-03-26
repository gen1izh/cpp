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


NewArhitectElementDialog::~NewArhitectElementDialog()
{
    delete ui;
}


void NewArhitectElementDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    ui->parentIdLabel->setText(
                Core::Base::instance().getParameterValue(QString("ArchitectElement_ParentId"), QString("")));
}

/*
 * Нажать на кнопку Ok
 */
void NewArhitectElementDialog::on_buttonBox_accepted()
{
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());

    QDjangoQuerySet<ArchitectElement> someArchitectElements;
    someArchitectElements = someArchitectElements.filter(QDjangoWhere("name",
                                                                      QDjangoWhere::Equals,
                                                                      ui->nameEdit->text()));

    if (someArchitectElements.size()>0) {
         messageLibrary msg;
         msg.createWarnMessage("Предупреждение",
                               "Элемент с идентификатором " +  ui->nameEdit->text() + " уже есть!"\
                                "Должен быть только один элемент c таким именем!");
    }
    else {
        ArchitectElement ae;
        bool ok;
        ae.setName(ui->nameEdit->text());
        ae.setType(ui->typeEdit->text());
        ae.setParentId(ui->parentIdLabel->text().toInt(&ok, 10));
        ae.save();
    }
}


