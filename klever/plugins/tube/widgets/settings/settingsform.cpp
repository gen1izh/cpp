#include "settingsform.h"
#include "ui_settingsform.h"
#include <frameWork/plugins.h>


SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    ui->editButton->setEnabled(false);

    Update();
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::Update() {
    QHashIterator<QString, Parameter *> m_parameters = Core::Base::instance().params();
    QHashIterator<QString, Parameter *> i(m_parameters);

    int k = 0;

    ui->keysListWidget->clear();

    while (i.hasNext()) {
      i.next();
      ui->keysListWidget->addItem(i.key());
      k++;
    }
}

void SettingsForm::on_keysListWidget_activated(const QModelIndex &index)
{
    QHashIterator<QString, Parameter *> m_parameters = Core::Base::instance().params();
    QHashIterator<QString, Parameter *> i(m_parameters);

    QString key = index.data().toString();

    ui->keyLabel->setText(key);

    while (i.hasNext()) {
        i.next();
        if (key == i.key()) {
            ui->valueEdit->setText(i.value()->getValue().toString());
        }
    }

    ui->editButton->setEnabled(true);
}


void SettingsForm::on_editButton_clicked()
{
    Core::Base::instance().setParameterValue(ui->keyLabel->text(),
                                             ui->valueEdit->text());
    ui->keyLabel->setText("");
    ui->valueEdit->setText("");
    ui->editButton->setEnabled(false);
}

void SettingsForm::on_updateButton_clicked()
{
    Update();
    ui->keyLabel->setText("");
    ui->valueEdit->setText("");
    ui->editButton->setEnabled(false);
}
