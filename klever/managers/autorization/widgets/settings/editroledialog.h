#ifndef EDITROLEDIALOG_H
#define EDITROLEDIALOG_H

#include <QDialog>

namespace Ui {
class EditRoleDialog;
}

class EditRoleDialog : public QDialog
{
  Q_OBJECT

public:
  explicit EditRoleDialog(QWidget *parent = 0);
  ~EditRoleDialog();

private:
  Ui::EditRoleDialog *ui;
};

#endif // EDITROLEDIALOG_H
