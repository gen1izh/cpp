#ifndef cintegration_SETTINGS_H
#define cintegration_SETTINGS_H

#include <QWidget>

class cintegrationSettings : public QWidget
{
    Q_OBJECT

    void createConnectors();

public:
    explicit cintegrationSettings(QWidget *parent = 0);

signals:

};

#endif // cintegration_SETTINGS_H
