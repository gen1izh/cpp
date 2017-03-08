#ifndef analysis_SETTINGS_H
#define analysis_SETTINGS_H

#include <QWidget>

class analysisSettings : public QWidget
{
    Q_OBJECT

    void createConnectors();

public:
    explicit analysisSettings(QWidget *parent = 0);

signals:

};

#endif // analysis_SETTINGS_H
