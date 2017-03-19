#ifndef ADDROLEDIALOG_H
#define ADDROLEDIALOG_H

#include <QDialog>

#include "models/rolemodel.h"

namespace Ui {
class AddRoleDialog;
}

class AddRoleDialog : public QDialog
{
    Q_OBJECT

    RoleModel        *m_modelRoles;

public:
    explicit AddRoleDialog(QWidget *parent = 0);
    ~AddRoleDialog();

    QString name() const;

    RoleModel *modelRoles() const;
    void setModelRoles(RoleModel *modelRoles);

protected:
    void showEvent(QShowEvent *);

private slots:

    void on_buttonBox_accepted();

private:
    Ui::AddRoleDialog *ui;
};

#endif // ADDROLEDIALOG_H
