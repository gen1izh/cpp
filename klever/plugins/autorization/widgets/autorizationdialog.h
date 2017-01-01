#ifndef AUTORIZATIONDIALOG_H
#define AUTORIZATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AutorizationDialog;
}

class AutorizationDialog : public QDialog
{
    Q_OBJECT

    bool m_autorizatedSuccessful = false;

public:
    explicit AutorizationDialog(QWidget *parent = 0);
    ~AutorizationDialog();

    bool autorizatedSuccessful() const;

private:
    Ui::AutorizationDialog *ui;

protected:
     void showEvent(QShowEvent *event);

private slots:
     void on_buttonBox_accepted();
};

#endif // AUTORIZATIONDIALOG_H
