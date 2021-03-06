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

struct architectElementListItem{
    int id;
    int parentId;
    QString name;
    QString type;
};


class BF_ArchitectForm : public QWidget
{
    Q_OBJECT

    QTreeWidgetItem *m_currentArchitectTreeItem;
    int m_currentArchitectTreeColumn;

public:
    explicit BF_ArchitectForm(QWidget *parent = 0);
    ~BF_ArchitectForm();

protected:
    void showEvent(QShowEvent *event);

signals:
    void openTexteditor();

private slots:
    void on_editArchitectElementButton_clicked();
    void on_addArchitectElementButton_clicked();
    void on_deleteArchitectElementButton_clicked();
    void readArchitecture();
    void on_architectTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_setLinkButton_clicked();
    void on_updateButton_clicked();
    void on_linkListWidget_currentTextChanged(const QString &currentText);
    void on_deleteLinkButton_clicked();
    void on_editorButton_clicked();
    void on_resetLinkBButton_clicked();
    void on_resetLinkAButton_clicked();
    void on_setLinkAButton_clicked();
    void on_setLinkBButton_clicked();

private:
    Ui::BF_ArchitectForm *ui;

    void recursiveDeleteElements(QTreeWidgetItem *item, int id);
};

#endif // BF_ARCHITECTFORM_H
