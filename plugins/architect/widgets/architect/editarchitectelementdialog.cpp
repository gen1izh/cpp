#include "editarchitectelementdialog.h"
#include "ui_editarchitectelementdialog.h"
#include <frameWork/base.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include "../../../_shared/db/models/architectelement.h"

#include <QDebug>

EditArchitectElementDialog::EditArchitectElementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditArchitectElementDialog)
{
    ui->setupUi(this);
}

EditArchitectElementDialog::~EditArchitectElementDialog()
{
    delete ui;
}

/*
 * Открываем окно редактирования элемента архитектуры
 */
void EditArchitectElementDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    ui->articleEdit->setText(Core::Base::instance().getParameterValue("ArchitectElement_Id",
                                                                      QString()));

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());

    QDjangoQuerySet<ArchitectElement> someArchitectElements;
    someArchitectElements = someArchitectElements.filter(QDjangoWhere("id",
                                                                      QDjangoWhere::Equals,
                                                                      ui->articleEdit->text()));

    ArchitectElement architectElement;
    if (someArchitectElements.size()>0) {
         someArchitectElements.at(0, &architectElement);
         ui->nameEdit->setText(architectElement.name());
         ui->typeEdit->setText(architectElement.type());
    }
}

/*
 * Обработчик кнопки Ok
 */
void EditArchitectElementDialog::on_buttonBox_accepted()
{

    Core::Base::instance().sessionDatabase()->transaction();

    QDjangoQuerySet<ArchitectElement> someArchitectElements;
    someArchitectElements = someArchitectElements.filter(QDjangoWhere("id",
                                                                      QDjangoWhere::Equals,
                                                                      ui->articleEdit->text()));

    ArchitectElement architectElement;
    if (someArchitectElements.size()>0) {
         someArchitectElements.at(0, &architectElement);
         architectElement.setName(ui->nameEdit->text());
         architectElement.setType(ui->typeEdit->text());
         architectElement.save();
    }
}
