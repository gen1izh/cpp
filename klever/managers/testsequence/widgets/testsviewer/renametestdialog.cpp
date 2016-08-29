#include "renametestdialog.h"
#include "ui_renametestdialog.h"

RenameTestDialog::RenameTestDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::RenameTestDialog)
{
  ui->setupUi(this);
}

RenameTestDialog::~RenameTestDialog()
{
  delete ui;
}

/*
 * Создание коннекторов
 */
void RenameTestDialog::createConnectors()
{
  connect(ui->testNameEdit, SIGNAL(textChanged(QString)), this, SLOT(on_testNameEdit_textChanged(QString)));
}

/*
 * Изменение имени тестовой последовательности
 */
void RenameTestDialog::on_testNameEdit_textChanged(QString txt)
{
  _text = txt;
}
