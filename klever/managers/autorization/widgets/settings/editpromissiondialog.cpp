#include "editpromissiondialog.h"
#include "ui_editpromissiondialog.h"

EditPromissionDialog::EditPromissionDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::EditPromissionDialog)
{
  ui->setupUi(this);
}

EditPromissionDialog::~EditPromissionDialog()
{
  delete ui;
}
