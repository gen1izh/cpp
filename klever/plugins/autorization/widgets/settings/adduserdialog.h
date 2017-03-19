#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

#include "models/userqdjangomodel.h"
#include "models/groupqdjangomodel.h"

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
  Group *group() const;
  QString password() const;

protected:
  void showEvent(QShowEvent *);
private slots:
  void on_addButton_clicked();

private:
  Ui::AddUserDialog *ui;
};

#endif // ADDUSERDIALOG_H
