#ifndef OPTIONSFORM_H
#define OPTIONSFORM_H

#include <QWidget>
#include <QStyleFactory>

namespace Ui {
class OptionsForm;
}

class OptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsForm(QWidget *parent = 0);
    ~OptionsForm();

protected:
    void showEvent(QShowEvent *event);
private slots:
    void on_acceptButton_clicked();

private:
    Ui::OptionsForm *ui;
};

#endif // OPTIONSFORM_H
