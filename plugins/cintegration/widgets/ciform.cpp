#include "ciform.h"
#include "ui_ciform.h"

CIForm::CIForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CIForm)
{
    ui->setupUi(this);
}

CIForm::~CIForm()
{
    delete ui;
}
