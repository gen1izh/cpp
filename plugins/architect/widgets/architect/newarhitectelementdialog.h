#ifndef NEWARHITECTELEMENTDIALOG_H
#define NEWARHITECTELEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class NewArhitectElementDialog;
}

class NewArhitectElementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewArhitectElementDialog(QWidget *parent = 0);
    ~NewArhitectElementDialog();

protected:
    void showEvent(QShowEvent *event);
private slots:
    void on_buttonBox_accepted();

    void on_checkButton_clicked();

private:
    Ui::NewArhitectElementDialog *ui;

    int addNewElement();

};

#endif // NEWARHITECTELEMENTDIALOG_H
