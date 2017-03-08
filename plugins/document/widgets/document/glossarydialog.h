#ifndef GLOSSARYDIALOG_H
#define GLOSSARYDIALOG_H

#include <QDialog>

namespace Ui {
class GlossaryDialog;
}

class GlossaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GlossaryDialog(QWidget *parent = 0);
    ~GlossaryDialog();

protected:
    void showEvent(QShowEvent *);
private slots:
    void on_buttonBox_accepted();

    void on_glossaryTable_cellClicked(int row, int column);

    void on_checkDublicatesButton_clicked();

private:
    Ui::GlossaryDialog *ui;
};

#endif // GLOSSARYDIALOG_H
