#include "addsessiondialog.h"
#include "ui_addsessiondialog.h"

AddSessionDialog::AddSessionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSessionDialog)
{
    ui->setupUi(this);
}

AddSessionDialog::~AddSessionDialog()
{
    delete ui;
}
QString AddSessionDialog::name() const
{
    return ui->nameEdit->text();
}


QString AddSessionDialog::parameters() const
{
    return QString("");
}



