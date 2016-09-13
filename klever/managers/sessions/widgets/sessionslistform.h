#ifndef SESSIONSLISTFORM_H
#define SESSIONSLISTFORM_H

#include <QWidget>

namespace Ui {
class SessionsListForm;
}

class SessionsListForm : public QWidget
{
    Q_OBJECT

public:
    explicit SessionsListForm(QWidget *parent = 0);
    ~SessionsListForm();

private:
    Ui::SessionsListForm *ui;
};

#endif // SESSIONSLISTFORM_H
