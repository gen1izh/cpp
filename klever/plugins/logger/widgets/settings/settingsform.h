#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include "../models/loggersettingsmodel.h"

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

    LoggerSettingsModel *m_loggerSettingsModel;

public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_loggerListWidget_clicked(const QModelIndex &index);

    void on_acceptButton_clicked();

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
