#ifndef EDITARCHITECTELEMENTDIALOG_H
#define EDITARCHITECTELEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class EditArchitectElementDialog;
}

class EditArchitectElementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditArchitectElementDialog(QWidget *parent = 0);
    ~EditArchitectElementDialog();

protected:
    void showEvent(QShowEvent *event);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditArchitectElementDialog *ui;
};

#endif // EDITARCHITECTELEMENTDIALOG_H
