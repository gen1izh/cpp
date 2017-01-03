#ifndef WATCHERFORM_H
#define WATCHERFORM_H

#include <QWidget>

namespace Ui {
class WatcherForm;
}

class WatcherForm : public QWidget
{
    Q_OBJECT

public:
    explicit WatcherForm(QWidget *parent = 0);
    ~WatcherForm();

private:
    Ui::WatcherForm *ui;
};

#endif // WATCHERFORM_H
