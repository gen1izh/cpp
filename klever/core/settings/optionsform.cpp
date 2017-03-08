#include "optionsform.h"
#include "ui_optionsform.h"
#include <frameWork/information.h>
#include <library/loggerapi/loggerapi.h>
#include <QFileDialog>

#include <library/message/messagelibrary.h>

#include <frameWork/base.h>

OptionsForm::OptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsForm)
{
    ui->setupUi(this);
    setObjectName(tr("Общие настройки приложения"));
}

OptionsForm::~OptionsForm()
{
    delete ui;
}


void OptionsForm::showEvent(QShowEvent *event) {

    ui->companyNameEdit->setText(Information::instance().company());

    ui->preffixSoftwareNameEdit->setText(Information::instance().softwareNamePrefix());
    ui->suffixSoftwareNameEdit->setText(Information::instance().softwareNameSuffix());
    ui->versionEdit->setText(Information::instance().version());
    ui->softwareNameEdit->setText(Information::instance().mainTitleApp());

    ui->aboutNameEdit->setText(Information::instance().aboutMessageTitle());
    ui->aboutTopEdit->setText(Information::instance().aboutMessageTop());
    ui->aboutBottomEdit->setText(Information::instance().aboutMessageBottom());

    ui->changelogEdit->setPlainText(Information::instance().changelog());

    ui->logoEdit->setText(Information::instance().logo());

    ui->styleBox->clear();
    ui->styleBox->addItem("fusion");
    ui->styleBox->addItem("windowsxp");
    ui->styleBox->addItem("windows");
    ui->styleBox->addItem("windowsvista");
    ui->styleBox->addItem("macintosh");

    ui->styleBox->setCurrentText(Information::instance().style());
    ui->pluginsList->clear();
    ui->pluginsList->addItems(Core::Plugins::instance().LoadListFromDatabase());
}

void OptionsForm::on_acceptButton_clicked()
{
    Information::instance().setCompany(ui->companyNameEdit->text());

    Information::instance().setSoftwareNamePrefix(ui->preffixSoftwareNameEdit->text());
    Information::instance().setSoftwareNameSuffix(ui->suffixSoftwareNameEdit->text());
    Information::instance().setVersion(ui->versionEdit->text());
    Information::instance().setMainTitleApp(ui->softwareNameEdit->text());

    Information::instance().setAboutMessageTitle(ui->aboutNameEdit->text());
    Information::instance().setAboutMessageTop(ui->aboutTopEdit->text());
    Information::instance().setAboutMessageBottom(ui->aboutBottomEdit->text());

    Information::instance().setChangelog(ui->changelogEdit->toPlainText());
    Information::instance().setStyle(ui->styleBox->currentText());
    Information::instance().setLogo(ui->logoEdit->text());
    Information::instance().saveApplicationInformation();

    QApplication::setStyle(QStyleFactory::create(Information::instance().style()));

    Library::LoggerApi::logInfo(this, "Настройки сохранены успешно!");

    messageLibrary msg;

    msg.createInfoMessage("Информация", "Настройки сохранены успешно!");
}

void OptionsForm::on_addButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Открыть плагин"), QCoreApplication::applicationDirPath(), tr("Dll (*.dll)"));

    QFileInfo f(fileName);

    bool isFind = false;

    for (int i = 0; i < ui->pluginsList->count(); i++)  {
        if (ui->pluginsList->item(i)->text() == f.baseName()) {
            isFind = true;
            break;
        }
    }

    if (!isFind) {
        ui->pluginsList->addItem(f.baseName());
        Core::Plugins::instance().AddNewPluginDatabase(f.baseName());
    }
    else {
        // Todo мессагу что есть уже...
    }

}

void OptionsForm::on_deleteButton_clicked()
{
    if (!ui->pluginsList->currentItem()->text().isEmpty()) {
        ui->pluginsList->removeItemWidget(ui->pluginsList->currentItem());
        Core::Plugins::instance().DeletePluginFromDatabase(ui->pluginsList->currentItem()->text());
        ui->pluginsList->clear();
        ui->pluginsList->addItems(Core::Plugins::instance().LoadListFromDatabase());
    }
}

void OptionsForm::on_logoBrowserButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Выбрать логотип"), QCoreApplication::applicationDirPath(), tr("png (*.png)"));

    if (!fileName.isEmpty()) {
        QFileInfo f(fileName);
        QString newFilename = QCoreApplication::applicationDirPath() + "/" + f.fileName();
        QFile::remove(newFilename);

        if (!QFile::copy(fileName, newFilename)) {
            messageLibrary msg;
            msg.createInfoMessage("Информация", "Не удается скопировать картинку. Возможно такой фаил уже есть!");

        }
        ui->logoEdit->setText(f.fileName());
    }
}
