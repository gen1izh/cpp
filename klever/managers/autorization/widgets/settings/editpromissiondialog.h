#ifndef EDITPROMISSIONDIALOG_H
#define EDITPROMISSIONDIALOG_H

#include <QDialog>

namespace Ui {
class EditPromissionDialog;
}

class EditPromissionDialog : public QDialog
{
  Q_OBJECT

public:
  explicit EditPromissionDialog(QWidget *parent = 0);
  ~EditPromissionDialog();

private:
  Ui::EditPromissionDialog *ui;
};

#endif // EDITPROMISSIONDIALOG_H
