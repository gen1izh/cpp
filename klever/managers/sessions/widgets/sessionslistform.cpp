#include "sessionslistform.h"
#include "ui_sessionslistform.h"

SessionsListForm::SessionsListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionsListForm)
{
    ui->setupUi(this);
}

SessionsListForm::~SessionsListForm()
{
    delete ui;
}
