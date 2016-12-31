#include "autorizationdialog.h"
#include "ui_autorizationdialog.h"

AutorizationDialog::AutorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutorizationDialog)
{
    ui->setupUi(this);
}

AutorizationDialog::~AutorizationDialog()
{
    delete ui;
}
