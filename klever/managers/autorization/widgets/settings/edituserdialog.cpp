#include "edituserdialog.h"
#include "ui_edituserdialog.h"

EditUserDialog::EditUserDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::EditUserDialog)
{
  ui->setupUi(this);
}

EditUserDialog::~EditUserDialog()
{
  delete ui;
}
