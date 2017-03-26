#ifndef PERSONALDATA_H
#define PERSONALDATA_H

#include <QWidget>
#include <QDebug>

#include "models/usermodel.h"
#include "models/groupmodel.h"
#include "models/promissionmodel.h"
#include "models/rolemodel.h"

namespace Ui {
class PersonalData;
}

class PersonalData : public QWidget
{
    Q_OBJECT

    GroupModel       *m_modelGroups;
    UserModel        *m_modelUsers;
    PromissionModel  *m_modelPromissions;
    RoleModel        *m_modelRoles;

public:
    explicit PersonalData(QWidget *parent = 0);
    ~PersonalData();

    void InitializeModels();

private slots:
    void on_addUserButton_clicked();

    void on_addGroupButton_clicked();

    void on_editGroupButton_clicked();

    void on_deleteGroupButton_clicked();

    void on_editUserButton_clicked();

    void on_deleteUserButton_clicked();

    void on_addPromissionButton_clicked();

    void on_deletePromissionButton_clicked();

    void on_addRoleButton_clicked();

    void on_editRoleButton_clicked();

    void on_deleteRoleButton_clicked();

    void on_promissionsView_clicked(const QModelIndex &index);

private:
    Ui::PersonalData *ui;
};

#endif // PERSONALDATA_H
