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
