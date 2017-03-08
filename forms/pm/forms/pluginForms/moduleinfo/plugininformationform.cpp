#include "plugininformationform.h"
#include "ui_plugininformationform.h"

#include <frameWork/base.h>

PluginInformationForm::PluginInformationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PluginInformationForm)
{
    ui->setupUi(this);
}

PluginInformationForm::~PluginInformationForm()
{
    delete ui;
}


void PluginInformationForm::showEvent(QShowEvent *event) {
Q_UNUSED(event)
    QHash<QString, PluginInterface *> hash = Core::Plugins::instance().plugins();
    ui->pluginsListWidget->clear();
    QHashIterator<QString, PluginInterface *> i(hash);
    while (i.hasNext()) {
        i.next();
        ui->pluginsListWidget->addItem(i.key());
    }

}

void PluginInformationForm::on_pluginsListWidget_clicked(const QModelIndex &index)
{
    QString plugin = index.data().toString();

    QHash<QString, PluginInterface *> hash = Core::Plugins::instance().plugins();
    QHashIterator<QString, PluginInterface *> i(hash);
    while (i.hasNext()) {
        i.next();
        if (i.key() == plugin) {
            ui->pluginInformationEdit->setPlainText(i.value()->information());
            break;
        }
    }
}
