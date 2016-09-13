#ifndef INFORMATION_DIALOG_H
#define INFORMATION_DIALOG_H

#include <QDialog>

namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialog(QWidget *parent = 0);
    ~InformationDialog();

private:
    Ui::InformationDialog *ui;
};

#endif // INFORMATION_DIALOG_H
