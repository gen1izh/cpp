#include "watcherform.h"
#include "ui_watcherform.h"

LoggerModel *WatcherForm::loggerModel() const
{
    return m_loggerModel;
}

WatcherForm::WatcherForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WatcherForm)
{
    ui->setupUi(this);

    m_loggerModel = new LoggerModel();
}

WatcherForm::~WatcherForm()
{
    delete ui;
}


void WatcherForm::showEvent(QShowEvent *event) {
    //    ui->sourcesList->addItems(m_loggerModel->getSources());

    foreach (const QString &st, m_loggerModel->getSources()) {
        QListWidgetItem* item = new QListWidgetItem(st, ui->sourcesList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Unchecked); // AND initialize check state
    }
}

void WatcherForm::on_loadButton_clicked()
{
    QStringList sources;

    for (int i = 0; i < ui->sourcesList->count(); i++) {
        if (ui->sourcesList->item(i)->checkState() == Qt::Checked) {
            sources.append(ui->sourcesList->item(i)->text());
        }

    }

    QStringList result = m_loggerModel->filtredMessages(QString(""), QString(""),
                                                    ui->errorBox->isChecked(),
                                                    ui->warningBox->isChecked(),
                                                    ui->informationBox->isChecked(),
                                                    sources);

    ui->logBrowser->clear();

    foreach (const QString &st, result) {
        ui->logBrowser->append(st);
    }

}
