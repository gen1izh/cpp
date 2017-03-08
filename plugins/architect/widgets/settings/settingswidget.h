#ifndef architect_SETTINGS_H
#define architect_SETTINGS_H

#include <QWidget>

class architectSettings : public QWidget
{
    Q_OBJECT

    void createConnectors();

public:
    explicit architectSettings(QWidget *parent = 0);

signals:

};

#endif // architect_SETTINGS_H
