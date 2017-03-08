#ifndef umldesigner_SETTINGS_H
#define umldesigner_SETTINGS_H

#include <QWidget>

class umldesignerSettings : public QWidget
{
    Q_OBJECT

    void createConnectors();

public:
    explicit umldesignerSettings(QWidget *parent = 0);

signals:

};

#endif // umldesigner_SETTINGS_H
