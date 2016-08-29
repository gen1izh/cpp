#ifndef ADDPROMISSIONDIALOG_H
#define ADDPROMISSIONDIALOG_H

#include <QDialog>

namespace Ui {
class AddPromissionDialog;
}

class AddPromissionDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AddPromissionDialog(QWidget *parent = 0);
  ~AddPromissionDialog();

private:
  Ui::AddPromissionDialog *ui;
};

#endif // ADDPROMISSIONDIALOG_H
