#ifndef CIFORM_H
#define CIFORM_H

#include <QWidget>

namespace Ui {
class CIForm;
}

class CIForm : public QWidget
{
    Q_OBJECT

public:
    explicit CIForm(QWidget *parent = 0);
    ~CIForm();

private:
    Ui::CIForm *ui;
};

#endif // CIFORM_H
