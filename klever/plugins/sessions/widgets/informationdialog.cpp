#include "informationdialog.h"
#include "ui_informationdialog.h"

#include <frameWork/base.h>

void InformationDialog::setModel(SessionsModel *model)
{
    m_model = model;
}

InformationDialog::InformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
}

InformationDialog::~InformationDialog()
{
    delete ui;
}

void InformationDialog::showEvent(QShowEvent *) {

    QString selectedSessionName =
            Core::Base::instance().getParameterValue(QString("[Session]SelectedName"),
                                                     QString(""));
    QString text = m_model->getSessionInformation(selectedSessionName);

    ui->informationEdit->clear();
    ui->informationEdit->setPlainText(text);
}

void InformationDialog::on_buttonBox_accepted()
{

    QString selectedSessionName =
            Core::Base::instance().getParameterValue(QString("[Session]SelectedName"),
                                                     QString(""));
    m_model->setSessionInformation(selectedSessionName,
                                          ui->informationEdit->toPlainText());
}
