#ifndef NEWREQUIREMENTDIALOG_H
#define NEWREQUIREMENTDIALOG_H

#include <QDialog>

#include "newrequirementdialog.h"

namespace Ui {
class NewRequirementDialog;
}

class NewRequirementDialog : public QDialog
{
    Q_OBJECT

    enum {
        MAX_REQUIREMENT_COUNT = 2000
    };

public:
    explicit NewRequirementDialog(QWidget *parent = 0);
    ~NewRequirementDialog();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_buttonBox_accepted();

    void on_componentBox_currentTextChanged(const QString &arg1);

private:
    Ui::NewRequirementDialog *ui;

};

#endif // NEWREQUIREMENTDIALOG_H
