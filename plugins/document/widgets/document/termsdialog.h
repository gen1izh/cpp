#ifndef TERMSDIALOG_H
#define TERMSDIALOG_H

#include <QDialog>

namespace Ui {
class TermsDialog;
}

class Term {
    QString m_name;
    QString m_description;

    public:
        Term();


        QString name() const;
        void setName(const QString &name);

        QString description() const;
        void setDescription(const QString &description);
};

class TermsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TermsDialog(QWidget *parent = 0);
    ~TermsDialog();

protected:
    void showEvent(QShowEvent *);
private slots:

    void on_buttonBox_accepted();
    void on_termsTable_cellClicked(int row, int column);
    void on_checkDuplicatesButton_clicked();

private:
    Ui::TermsDialog *ui;
    bool caseInsensitiveLessThan(Term t1, Term t2);
};

#endif // TERMSDIALOG_H
