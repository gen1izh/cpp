#include "sessionslistform.h"
#include "ui_sessionslistform.h"
#include <QTimer>
#include <frameWork/base.h>

SessionsListForm::SessionsListForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SessionsListForm)
{
    ui->setupUi(this);

    m_model = new SessionsModel();

    ui->sessionsView->setModel(m_model);
}

SessionsListForm::~SessionsListForm()
{
    delete ui;
}

void SessionsListForm::showEvent(QShowEvent *) {
    m_model->updateModel();
}

void SessionsListForm::on_openButton_clicked()
{
    QString path = QString("%1/sessions/%2")
                            .arg(QCoreApplication::applicationDirPath())
                            .arg(ui->sessionsView->currentIndex().data().toString());


    Core::Base::instance().setParameterValue(QString("[Session]Folder"), path);
    QDir dir(path);
    if (!dir.exists()) {
        if (!dir.mkpath(path)) {
            Library::LoggerApi::logError(this, "Каталог сессии не создан!");
        }
    }

    Core::Base::instance().setParameterValue(QString("[Session]Name"),
                                             ui->sessionsView->currentIndex().data().toString());

    Core::Base::instance().initializeSessionDatabase(ui->sessionsView->currentIndex().data().toString());

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
        ui->openButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->informationButton->setEnabled(false);
        ui->dublicateButton->setEnabled(false);
    }

}

void SessionsListForm::on_deleteButton_clicked()
{
    m_model->deleteSession(ui->sessionsView->currentIndex());
    m_model->updateModel();
    ui->openButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->informationButton->setEnabled(false);
    ui->dublicateButton->setEnabled(false);
}

void SessionsListForm::on_informationButton_clicked()
{
    QScopedPointer<InformationDialog> dialog(new InformationDialog);

    dialog.data()->setModel(m_model);

    Core::Base::instance().setParameterValue(QString("[Session]SelectedName"),
                                             ui->sessionsView->currentIndex().data().toString() );


    if (dialog.data()->exec() == QDialog::Accepted) {

    }

}

void SessionsListForm::on_dublicateButton_clicked()
{
    QScopedPointer<CloneDialog> dialog(new CloneDialog);

    Core::Base::instance().setParameterValue(QString("[Session]SelectedName"),
                                             ui->sessionsView->currentIndex().data().toString() );

    if (dialog.data()->exec() == QDialog::Accepted) {
        QString name = Core::Base::instance().getParameterValue(QString("[Session]CloneName"),
                                                                QString(""));
        m_model->dublicateSession(ui->sessionsView->currentIndex(), name);
        m_model->updateModel();
        ui->openButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->informationButton->setEnabled(false);
        ui->dublicateButton->setEnabled(false);
    }
}

/*
 *
 */
void SessionsListForm::on_sessionsView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        ui->openButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->informationButton->setEnabled(true);
        ui->dublicateButton->setEnabled(true);
    }
    else {
        ui->openButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->informationButton->setEnabled(false);
        ui->dublicateButton->setEnabled(false);
    }
}
