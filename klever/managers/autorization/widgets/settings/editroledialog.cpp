#include "editroledialog.h"
#include "ui_editroledialog.h"

EditRoleDialog::EditRoleDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::EditRoleDialog)
{
  ui->setupUi(this);
}

EditRoleDialog::~EditRoleDialog()
{
  delete ui;
}
