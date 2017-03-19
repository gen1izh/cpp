#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>

#include "models/groupqdjangomodel.h"

namespace Ui {
class EditUserDialog;
}

class EditUserDialog : public QDialog
{
  Q_OBJECT

  QString m_username="";
  QString m_password="";
  QString m_group="";

public:
    explicit EditUserDialog(QWidget *parent = 0, QString username = "");
    ~EditUserDialog();

    QString username() const;
    Group *group() const;
    QString password() const;

protected:
    void showEvent(QShowEvent *);
private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::EditUserDialog *ui;
};

#endif // EDITUSERDIALOG_H
