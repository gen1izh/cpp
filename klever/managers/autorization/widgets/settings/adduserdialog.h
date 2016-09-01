#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AddUserDialog(QWidget *parent = 0);
  ~AddUserDialog();

  QString username() const;
  QString group() const;
  QString password() const;

private slots:
  void on_addButton_clicked();

private:
  Ui::AddUserDialog *ui;
};

#endif // ADDUSERDIALOG_H
