#ifndef document_SETTINGS_H
#define document_SETTINGS_H

#include <QWidget>

class documentSettings : public QWidget
{
    Q_OBJECT

    void createConnectors();

public:
    explicit documentSettings(QWidget *parent = 0);

signals:

};

#endif // document_SETTINGS_H
