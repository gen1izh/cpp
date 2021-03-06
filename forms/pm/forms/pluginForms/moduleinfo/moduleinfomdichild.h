#ifndef PLUGININFOMDICHILD_H
#define PLUGININFOMDICHILD_H

#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>

#include <frameWork/base.h>
#include "plugininformationform.h"


class PluginInfoMdiChild : public QWidget {

    Q_OBJECT

    PluginInformationForm *m_pluginWidget;

    signals:
        void setVisibleSignal(bool visible);

public:

    PluginInfoMdiChild();
    ~PluginInfoMdiChild();

    void closeEvent(QCloseEvent *event);
    void resizeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

};

#endif // PLUGININFOMDICHILD_H
