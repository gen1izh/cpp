#ifndef texteditor_SETTINGS_H
#define texteditor_SETTINGS_H

#include <QWidget>

class texteditorSettings : public QWidget
{
    Q_OBJECT

    void createConnectors();

public:
    explicit texteditorSettings(QWidget *parent = 0);

signals:

};

#endif // texteditor_SETTINGS_H
