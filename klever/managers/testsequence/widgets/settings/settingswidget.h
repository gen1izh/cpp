#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class TestsequenceSettingsWidget;
}

class TestsequenceSettingsWidget : public QWidget
{
    Q_OBJECT

  QString _editorPath;

  void initializeWidget();

  void createConnectors();

public:
    explicit TestsequenceSettingsWidget(QWidget *parent = 0);
    ~TestsequenceSettingsWidget();

  QString getEditorPath();
  void setEditorPath(QString path);

private slots:

  /*!
   * \brief Открытие диалогового окна
   * Необходимо для выбора редактора скриптов
   */
  void openPathDialog();

  void on_saveButton_clicked();

  void on_abortAfterErrorBox_stateChanged(int arg1);

private:
  Ui::TestsequenceSettingsWidget *ui;

};

#endif // SETTINGSWIDGET_H
