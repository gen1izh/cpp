#ifndef EDITGROUPDIALOG_H
#define EDITGROUPDIALOG_H

#include <QDialog>

namespace Ui {
class EditGroupDialog;
}

class EditGroupDialog : public QDialog
{
  Q_OBJECT

  QString m_role="";
  QString m_description="";
  QString m_name="";
  QString m_parent="";

public:
  explicit EditGroupDialog(QWidget *parent = 0, QString groupName = "");
  ~EditGroupDialog();

  QString name() const;
  QString parent() const;
  QString role() const;
  QString description() const;

private:
  Ui::EditGroupDialog *ui;
};

#endif // EDITGROUPDIALOG_H
