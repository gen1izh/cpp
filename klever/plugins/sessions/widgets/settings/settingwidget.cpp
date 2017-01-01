#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::initialize()
{
    // Считать из БД строку с параметрами

    // распарсить ее

    // забить сюда в качестве таблицы параметров

    // Установить глоабльные параметры ....



//    QVariantMap parameter;
//    for (int i = 0; i < ui->parametersWidget->rowCount(); i++) {
//        if (ui->parametersWidget->item(i, 0)!=NULL) {
//            QString key = ui->parametersWidget->item(i, 0)->text();
//            QString value = ui->parametersWidget->item(i, 1)->text();
//            parameter.insert(key, value);
//        }
//    }

//    QJsonDocument doc(QJsonObject::fromVariantMap(parameter));
//    m_parameters = doc.toJson();
}
