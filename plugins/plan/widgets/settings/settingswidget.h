#ifndef plan_SETTINGS_H
#define plan_SETTINGS_H

#include <QWidget>

class planSettings : public QWidget
{
    Q_OBJECT

    void createConnectors();

public:
    explicit planSettings(QWidget *parent = 0);

signals:

};

#endif // plan_SETTINGS_H
