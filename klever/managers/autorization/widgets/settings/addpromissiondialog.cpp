#include "addpromissiondialog.h"
#include "ui_addpromissiondialog.h"

AddPromissionDialog::AddPromissionDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddPromissionDialog)
{
  ui->setupUi(this);
}

AddPromissionDialog::~AddPromissionDialog()
{
  delete ui;
}
