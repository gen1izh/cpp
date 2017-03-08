#ifndef WATCHERFORM_H
#define WATCHERFORM_H

#include <QWidget>
#include "models/loggermodel.h"

namespace Ui {
class WatcherForm;
}

class WatcherForm : public QWidget
{
    Q_OBJECT
    LoggerModel *m_loggerModel;

public:
    explicit WatcherForm(QWidget *parent = 0);
    ~WatcherForm();

    LoggerModel *loggerModel() const;

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_loadButton_clicked();

private:
    Ui::WatcherForm *ui;
};

#endif // WATCHERFORM_H
