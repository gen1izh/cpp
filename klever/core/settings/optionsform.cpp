#include "optionsform.h"
#include "ui_optionsform.h"
#include <frameWork/information.h>
#include <library/loggerapi/loggerapi.h>

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

    ui->styleBox->clear();
    ui->styleBox->addItem("fusion");
    ui->styleBox->addItem("windowsxp");
    ui->styleBox->addItem("windows");
    ui->styleBox->addItem("windowsvista");
    ui->styleBox->addItem("macintosh");

    ui->styleBox->setCurrentText(Information::instance().style());

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

    Information::instance().saveApplicationInformation();

    QApplication::setStyle(QStyleFactory::create(Information::instance().style()));

    Library::LoggerApi::logInfo(this, "Настройки сохранены успешно!");
}
