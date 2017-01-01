#include "clonedialog.h"
#include "ui_clonedialog.h"
#include <frameWork/base.h>

CloneDialog::CloneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloneDialog)
{
    ui->setupUi(this);
}

CloneDialog::~CloneDialog()
{
    delete ui;
}


void CloneDialog::showEvent(QShowEvent *) {
    QString name = Core::Base::instance().getParameterValue(QString("[Session]SelectedName"),
                                                            QString(""));
    ui->nameLabel->setText(name);
}

void CloneDialog::on_buttonBox_accepted()
{
    Core::Base::instance().setParameterValue(QString("[Session]CloneName"),
                                             ui->cloneNameEdit->text() );
}
