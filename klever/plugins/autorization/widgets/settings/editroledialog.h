#ifndef EDITROLEDIALOG_H
#define EDITROLEDIALOG_H

#include <QDialog>

namespace Ui {
class EditRoleDialog;
}

class EditRoleDialog : public QDialog
{
  Q_OBJECT

  QString m_name="";

  QString m_promission="";

public:
  explicit EditRoleDialog(QWidget *parent = 0, QString name = "");
  ~EditRoleDialog();

  QString promission() const;
  QString name() const;
private slots:
  void on_addButton_clicked();

  void on_deleteButton_clicked();

private:
  Ui::EditRoleDialog *ui;
};

#endif // EDITROLEDIALOG_H
