#ifndef ADD_PROMISSION_DIALOG_H
#define ADD_PROMISSION_DIALOG_H

#include <QDialog>

#include "models/promissionqdjangomodel.h"
#include "models/promissionmodel.h"

#include "models/roleqdjangomodel.h"

namespace Ui {
class AddPromissionDialog;
}

class AddPromissionDialog : public QDialog
{
    Q_OBJECT

    PromissionModel *m_modelPromissions;

public:
    explicit AddPromissionDialog(QWidget *parent = 0);
    ~AddPromissionDialog();

    QString name() const;
    QString signature() const;

    PromissionModel *modelPromissions() const;
    void setModelPromissions(PromissionModel *modelPromissions);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddPromissionDialog *ui;

protected:
    void showEvent(QShowEvent *);
};

#endif // ADD_PROMISSION_DIALOG_H
