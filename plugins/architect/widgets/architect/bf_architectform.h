#ifndef BF_ARCHITECTFORM_H
#define BF_ARCHITECTFORM_H

#include <QTreeWidget>
#include <QWidget>

#include "newarhitectelementdialog.h"
#include "editarchitectelementdialog.h"
#include <library/message/messagelibrary.h>
namespace Ui {
class BF_ArchitectForm;
}

class BF_ArchitectForm : public QWidget
{
    Q_OBJECT

    QTreeWidgetItem *m_currentArchitectTreeItem;
    int m_currentArchitectTreeColumn;

public:
    explicit BF_ArchitectForm(QWidget *parent = 0);
    ~BF_ArchitectForm();

private slots:
    void on_editArchitectElementButton_clicked();

    void on_addArchitectElementButton_clicked();

    void on_deleteArchitectElementButton_clicked();

    void openArchitect();
    void on_architectTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_resetButton_clicked();

    void on_setLinkButton_clicked();

    void on_updateButton_clicked();

    void on_linkListWidget_currentTextChanged(const QString &currentText);

    void on_deleteLinkButton_clicked();

    void on_changeButton_clicked();

    void on_saveAliasButton_clicked();

private:
    Ui::BF_ArchitectForm *ui;

    QTreeWidgetItem *findItemByTypeAndOrArticle(const QString &type, const QString &article = QString());
};

#endif // BF_ARCHITECTFORM_H
