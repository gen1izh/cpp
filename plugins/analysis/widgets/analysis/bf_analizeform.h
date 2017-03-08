#ifndef BF_ANALIZEFORM_H
#define BF_ANALIZEFORM_H

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
        DOMAIN_AREA,
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
private slots:
    void onContextAnalyzeTreeMenuRequest(QPoint point);
    void on_updateButton_clicked();
    void openRequirementDialog();
    bool fillRequirements(const QString &rtype, QTreeWidgetItem *reqItem);
    void on_onEditorButton_clicked();

    void on_analyzeTreeWidget_clicked(const QModelIndex &index);
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_editButton_clicked();

};

#endif // BF_ANALIZEFORM_H
