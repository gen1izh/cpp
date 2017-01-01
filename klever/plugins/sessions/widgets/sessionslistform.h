#ifndef SESSIONS_LIST_FORM_H
#define SESSIONS_LIST_FORM_H

#include <QDialog>
#include "models/sessionsmodel.h"

#include "addsessiondialog.h"
#include "clonedialog.h"
#include "informationdialog.h"

namespace Ui {
class SessionsListForm;
}

class SessionsListForm : public QDialog
{
    Q_OBJECT
    SessionsModel *m_model;

public:
    explicit SessionsListForm(QWidget *parent = 0);
    ~SessionsListForm();

protected:
    void showEvent(QShowEvent *);

private slots:
    void on_openButton_clicked();

    void on_exitButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_informationButton_clicked();

    void on_dublicateButton_clicked();

    void on_sessionsView_clicked(const QModelIndex &index);

private:
    Ui::SessionsListForm *ui;
};

#endif // SESSIONS_LIST_FORM_H
