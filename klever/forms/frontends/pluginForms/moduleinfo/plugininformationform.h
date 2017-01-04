#ifndef PLUGININFORMATIONFORM_H
#define PLUGININFORMATIONFORM_H

#include <QWidget>

namespace Ui {
class PluginInformationForm;
}

class PluginInformationForm : public QWidget
{
    Q_OBJECT

public:
    explicit PluginInformationForm(QWidget *parent = 0);
    ~PluginInformationForm();

protected:
    void showEvent(QShowEvent *event);
private slots:
    void on_pluginsListWidget_clicked(const QModelIndex &index);

private:
    Ui::PluginInformationForm *ui;
};

#endif // PLUGININFORMATIONFORM_H
