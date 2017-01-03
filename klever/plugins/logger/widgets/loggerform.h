#ifndef LOGGERFORM_H
#define LOGGERFORM_H

#include <QWidget>

namespace Ui {
class LoggerForm;
}

class LoggerForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoggerForm(QWidget *parent = 0);
    ~LoggerForm();

    void appendText(const QString & txt);

private:
    Ui::LoggerForm *ui;
};

#endif // LOGGERFORM_H
