#include "addroledialog.h"
#include "ui_addroledialog.h"

AddRoleDialog::AddRoleDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddRoleDialog)
{
  ui->setupUi(this);
}

AddRoleDialog::~AddRoleDialog()
{
  delete ui;
}
