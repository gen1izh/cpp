#ifndef taskmaster_SETTINGS_H
#define taskmaster_SETTINGS_H

#include <QWidget>

class taskmasterSettings : public QWidget
{
    Q_OBJECT

    void createConnectors();

public:
    explicit taskmasterSettings(QWidget *parent = 0);

signals:

};

#endif // taskmaster_SETTINGS_H
