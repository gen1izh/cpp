#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include <QTableWidgetItem>

namespace Ui {
    class MainWindow;
}

class
    MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  QTableWidgetItem *opcode;
  QTableWidgetItem *errorMode;
  QTableWidgetItem *intrTrap;
  QTableWidgetItem *pc;
  QTableWidgetItem *ldStParam;
  QTableWidgetItem *ttc;
  QTableWidgetItem *mci;
  QTableWidgetItem *ibh;

private slots:

  void on_deviceBrowserButton_clicked();

  void on_deviceListBox_currentIndexChanged(int index);

  void on_dsuEnableBox_clicked();

  void on_dsuBreakBox_clicked();

  void on_dsuActivUpdate();

  void on_wmemButton_clicked();

  void on_memButton_clicked();

  void on_fileBrowserEELoadButton_clicked();

  void on_eeloadButton_clicked();

  void on_dsuEnableBox_toggled(bool checked);

  void on_dsuBreakBox_toggled(bool checked);

  void on_startPortAButton_clicked();

  void on_stopPortAButton_clicked();

  void on_dsuRegsUpdateButton_clicked();

  void on_dsucViewTable_cellPressed(int row, int column);

  void on_dsucViewTable_cellEntered(int row, int column);

  void on_dsucViewTable_cellChanged(int row, int column);

  void on_tbctlViewTable_cellChanged(int row, int column);

  void on_ttcViewTable_cellChanged(int row, int column);

  void on_bad1ViewTable_cellChanged(int row, int column);

  void on_bad2ViewTable_cellChanged(int row, int column);

  void on_bma1ViewTable_cellChanged(int row, int column);

  void on_bma2ViewTable_cellChanged(int row, int column);

public slots:
  void systemLogRefresh();
  void protoLogRefresh();
  void traceBufferViewRefresh();
  void traceBufferViewInit();
private:
    Ui::MainWindow *ui;

    QTimer *timer;
};

#endif // MAINWINDOW_H
