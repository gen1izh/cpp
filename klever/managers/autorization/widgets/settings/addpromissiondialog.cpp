#include "addpromissiondialog.h"
#include "ui_addpromissiondialog.h"
#include <QRegExp>
#include <QRegExpValidator>

AddPromissionDialog::AddPromissionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPromissionDialog)
{

    ui->setupUi(this);

    QRegExp rx0("^(\\w+\\s+)$");
    QValidator *validator0 = new QRegExpValidator(rx0, this);

    ui->promissionEdit->setValidator(validator0);

    QRegExp rx1("^([A-Z0-9]+)$");
    QValidator *validator1 = new QRegExpValidator(rx1, this);

    ui->signatureEdit->setValidator(validator1);
}

AddPromissionDialog::~AddPromissionDialog()
{
  delete ui;
}

QString AddPromissionDialog::name() const
{
    return ui->promissionEdit->text();
}

QString AddPromissionDialog::signature() const
{
    return ui->signatureEdit->text();
}
