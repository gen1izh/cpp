#include "autorizationdialog.h"
#include "ui_autorizationdialog.h"
#include <frameWork/base.h>

#include "settings/models/usermodel.h"

bool AutorizationDialog::autorizatedSuccessful() const
{
    return m_autorizatedSuccessful;
}

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

void AutorizationDialog::showEvent(QShowEvent *event)
{
Q_UNUSED(event)
    QString sessionName = Core::Base::instance().getParameterValue(QString("[Session]Name"),
                                                                   QString(""));

    ui->sessionNameLabel->setText(sessionName);

    UserModel userModel;

    if (userModel.selectAllUsers().isEmpty()) {
        userModel.addUser(QString("Administrator"),
                          QString("admin"),
                          QString("Administrators"));
    }

    ui->usersBox->addItems(userModel.selectAllUsers());

}

void AutorizationDialog::on_buttonBox_accepted()
{
    UserModel userModel;
    QString pwd = userModel.getUserPasswordByName(ui->usersBox->currentText());

    if (pwd == ui->pwdEdit->text()) {
        Core::Base::instance().setParameterValue(QString("[Autorization]User"),
                                                 ui->usersBox->currentText());
        m_autorizatedSuccessful = true;
    }
}
