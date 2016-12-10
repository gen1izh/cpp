#include "sessionslistform.h"
#include "ui_sessionslistform.h"

SessionsListForm::SessionsListForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SessionsListForm)
{
    ui->setupUi(this);

    m_model = new SessionsModel();

    ui->sessionsView->setModel(m_model);
    m_model->updateModel();
}

SessionsListForm::~SessionsListForm()
{
    delete ui;
}

void SessionsListForm::on_openButton_clicked()
{
    accept();
}

void SessionsListForm::on_exitButton_clicked()
{
    reject();
}

void SessionsListForm::on_addButton_clicked()
{
    QScopedPointer<AddSessionDialog> dialog(new AddSessionDialog);

    if (dialog.data()->exec() == QDialog::Accepted) {
        m_model->addSession(dialog.data()->name(), dialog.data()->parameters());
        m_model->updateModel();
    }

}

void SessionsListForm::on_deleteButton_clicked()
{
    m_model->deleteSession(ui->sessionsView->currentIndex());
}

void SessionsListForm::on_informationButton_clicked()
{
    QScopedPointer<InformationDialog> dialog(new InformationDialog);

    if (dialog.data()->exec() == QDialog::Accepted) {

    }
}

void SessionsListForm::on_dublicateButton_clicked()
{
    m_model->dublicateSession(ui->sessionsView->currentIndex());
}

void SessionsListForm::on_renameButton_clicked()
{
    m_model->renameSession(ui->sessionsView->currentIndex(), ui->newNameEdit->text());
}
