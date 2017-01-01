#include "addsessiondialog.h"
#include "ui_addsessiondialog.h"

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

AddSessionDialog::AddSessionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSessionDialog)
{
    ui->setupUi(this);
}

AddSessionDialog::~AddSessionDialog()
{
    delete ui;
}
QString AddSessionDialog::name() const
{
    return ui->nameEdit->text();
}


QString AddSessionDialog::parameters() const
{
    return m_parameters;
}

void AddSessionDialog::on_buttonBox_accepted()
{
    QVariantMap parameter;
    for (int i = 0; i < ui->parametersWidget->rowCount(); i++) {
        if (ui->parametersWidget->item(i, 0)!=NULL) {
            QString key = ui->parametersWidget->item(i, 0)->text();
            QString value = ui->parametersWidget->item(i, 1)->text();
            parameter.insert(key, value);
        }
    }

    QJsonDocument doc(QJsonObject::fromVariantMap(parameter));
    m_parameters = doc.toJson();
}


