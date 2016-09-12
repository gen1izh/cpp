#ifndef ADDSESSIONDIALOG_H
#define ADDSESSIONDIALOG_H

#include <QDialog>

namespace Ui {
class AddSessionDialog;
}

class AddSessionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSessionDialog(QWidget *parent = 0);
    ~AddSessionDialog();

private:
    Ui::AddSessionDialog *ui;
};

#endif // ADDSESSIONDIALOG_H
