#ifndef BF_ANALIZEFORM_H
#define BF_ANALIZEFORM_H

#include <QListWidget>
#include <QTreeWidget>
#include <QWidget>

#include "newrequirementdialog.h"
#include "editrequirementdialog.h"


namespace Ui {
class BF_AnalizeForm;
}

class BF_AnalizeForm : public QWidget
{
    Q_OBJECT

    enum ANALYZE_TYPE {
        DEFAULT = -1,
        VISION,
        USER_REQUIREMENTS,
        FUNC_REQUIREMENTS,
        SUB_FUNC_REQUIREMENTS,
        NOFUNC_REQUIREMENTS,
        SUB_NOFUNC_REQUIREMENTS,
        COMMON_REQUIREMENTS,
        SUB_USER_REQUIREMENTS,
        SUB_COMMON_REQUIREMENTS,
        OTHER
    };

    QAction *m_openEditorAction;

    EditRequirementDialog *m_editRequirementDialog;
    NewRequirementDialog *m_requirementDialog;


public:
    explicit BF_AnalizeForm(QWidget *parent = 0);
    ~BF_AnalizeForm();

private:
    Ui::BF_AnalizeForm *ui;

    void createConnectors();
    void createActions();
    void createDialogs();

    void controlAccess(ANALYZE_TYPE val);
    void readRequirements();
private slots:
    void on_updateButton_clicked();
    void openRequirementDialog();
    void fillRequirements(const QString &type, QListWidget *lwgt);
    void on_onEditorButton_clicked();

    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_editButton_clicked();
    void on_requirementsTab_currentChanged(int index);
    void on_visionListWidget_clicked(const QModelIndex &index);
    void on_userRequirementListWidget_clicked(const QModelIndex &index);
    void on_funcRequirementListWidget_clicked(const QModelIndex &index);
    void on_nofuncRequirementListWidget_clicked(const QModelIndex &index);
    void on_commonRequirementListWidget_clicked(const QModelIndex &index);

signals:
    void openTexteditor();

protected:
    void showEvent(QShowEvent *event);
};

#endif // BF_ANALIZEFORM_H
