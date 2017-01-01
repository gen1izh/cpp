#ifndef INFORMATION_DIALOG_H
#define INFORMATION_DIALOG_H

#include <QDialog>
#include "models/sessionsmodel.h"
#include <QScopedPointer>

namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

    SessionsModel *m_model;

public:
    explicit InformationDialog(QWidget *parent = 0);
    ~InformationDialog();

    void setModel(SessionsModel *model);

protected:
    void showEvent(QShowEvent *);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::InformationDialog *ui;
};

#endif // INFORMATION_DIALOG_H
