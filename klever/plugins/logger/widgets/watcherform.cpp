#include "watcherform.h"
#include "ui_watcherform.h"

WatcherForm::WatcherForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WatcherForm)
{
    ui->setupUi(this);
}

WatcherForm::~WatcherForm()
{
    delete ui;
}
