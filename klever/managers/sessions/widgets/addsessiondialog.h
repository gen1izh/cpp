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

    QString name() const;

    QString parameters() const;

private:
    Ui::AddSessionDialog *ui;

    QString m_name;
    QString m_parameters;
};

#endif // ADDSESSIONDIALOG_H
