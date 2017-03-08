#ifndef EDITREQUIREMENTDIALOG_H
#define EDITREQUIREMENTDIALOG_H

#include <QDialog>

namespace Ui {
class EditRequirementDialog;
}

class EditRequirementDialog : public QDialog
{
    Q_OBJECT

    enum {
        MAX_REQUIREMENT_COUNT = 2000
    };

public:
    explicit EditRequirementDialog(QWidget *parent = 0);
    ~EditRequirementDialog();

protected:
    void showEvent(QShowEvent *event);
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_componentBox_currentTextChanged(const QString &arg1);

private:
    Ui::EditRequirementDialog *ui;
};

#endif // EDITREQUIREMENTDIALOG_H
