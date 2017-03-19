#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QDialog>

#include "models/groupqdjangomodel.h"
#include "models/roleqdjangomodel.h"

namespace Ui {
class addGroupDialog;
}

class AddGroupDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AddGroupDialog(QWidget *parent = 0);
  ~AddGroupDialog();

  QString name() const;
  QString parent() const;
  QString description() const;

protected:
  void showEvent(QShowEvent *);
private:
  Ui::addGroupDialog *ui;
};

#endif // ADDGROUPDIALOG_H
