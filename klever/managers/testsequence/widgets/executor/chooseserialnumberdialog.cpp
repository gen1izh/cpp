#include "chooseserialnumberdialog.h"
#include "ui_chooseserialnumberdialog.h"

chooseSerialNumberDialog::chooseSerialNumberDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::chooseSerialNumberDialog)
{
  ui->setupUi(this);
}

chooseSerialNumberDialog::~chooseSerialNumberDialog()
{
  delete ui;
}

/*
 * Возвращает серийный номер
 */
QString chooseSerialNumberDialog::getSerialNumber()
{
  return ui->serialNumberEdit->text();
}

/*
 * Устанавливает серийный номер
 */
void chooseSerialNumberDialog::setSerialNumber(QString sn)
{
  ui->serialNumberEdit->setText(sn);
}
