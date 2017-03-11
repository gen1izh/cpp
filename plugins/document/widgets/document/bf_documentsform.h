#ifndef BF_DOCUMENTSFORM_H
#define BF_DOCUMENTSFORM_H

#include <QWidget>
#include "termsdialog.h"
#include "glossarydialog.h"
#include <library/message/messagelibrary.h>

namespace Ui {
class BF_DocumentsForm;
}

class BF_DocumentsForm : public QWidget
{
    Q_OBJECT

    TermsDialog *m_termsDialog;
    GlossaryDialog *m_glossaryDialog;

public:
    explicit BF_DocumentsForm(QWidget *parent = 0);
    ~BF_DocumentsForm();

protected:
    void showEvent(QShowEvent *event);
private slots:
    void on_editButton_clicked();

    void on_createAppendixButton_clicked();

    void on_deleteAppendixButton_clicked();

    void on_terminButton_clicked();
    void on_glossaryButton_clicked();
    void on_generateDocumentsButton_clicked();

    void on_documentTreeWidget_doubleClicked(const QModelIndex &index);


signals:
    void openTexteditor();

private:
    Ui::BF_DocumentsForm *ui;
    void createDialogs();
};

#endif // BF_DOCUMENTSFORM_H
