#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();

private slots:
    void on_keysListWidget_activated(const QModelIndex &index);

    void Update();

    void on_editButton_clicked();

    void on_updateButton_clicked();

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
