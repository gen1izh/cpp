#include "settingsform.h"
#include "ui_settingsform.h"
#include "frameWork/base.h"

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    m_loggerSettingsModel = new LoggerSettingsModel();
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::showEvent(QShowEvent *event) {
    Q_UNUSED(event)
    ui->currentLoggerNameEdit->setText(m_loggerSettingsModel->getCurrentName());

    QString path = Core::Base::instance().getParameterValue(QString("[Session]Folder"), QString(""));
    path = QString("%1/logs").arg(path);

    QDir dir(path);
    QFileInfoList dirContent = dir.entryInfoList();

    foreach (const QFileInfo &fi, dirContent) {
        QString t = fi.baseName();
        t = t.trimmed();
        if (!t.isEmpty()) {
            ui->loggerListWidget->addItem(fi.baseName());
        }
    }
}

void SettingsForm::on_loggerListWidget_clicked(const QModelIndex &index)
{
    ui->currentLoggerNameEdit->setText(index.data().toString());
}

void SettingsForm::on_acceptButton_clicked()
{
    m_loggerSettingsModel->setCurrentName(ui->currentLoggerNameEdit->text());
}
