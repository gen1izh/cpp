#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QDialog>

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
  QString role() const;
  QString description() const;

private:
  Ui::addGroupDialog *ui;
};

#endif // ADDGROUPDIALOG_H
