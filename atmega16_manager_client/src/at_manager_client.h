#ifndef AT_MANAGER_CLIENT_H
#define AT_MANAGER_CLIENT_H

#include <QMainWindow>
#include "prt\cmd_packet.h"


extern QMap<QString, int> devMapNames;

namespace Ui {
class AT_manager_client;
}

class AvrClientApp : public QMainWindow {
    Q_OBJECT
    
public:
  explicit AvrClientApp(QWidget *parent = 0);
  ~AvrClientApp();

  void interfaceInitilize();

  void ATMC_debugTable_refresh();
  void ATMC_reportTree_Repaint();
  void ATMC_registers_Refresh();
  void ATMC_codeLineLight_Refresh(int popo);

  QToolBar* createToolBar() {
    QToolBar* ptb = new QToolBar("Linker ToolBar");

    ptb->addAction(QPixmap(""), "Run", this, SLOT(slotNoImpl()));
    ptb->addAction(QPixmap(""), "Translate", this, SLOT(slotNoImpl()));
    ptb->addAction(QPixmap(""), "Run", this, SLOT(slotNoImpl()));
    ptb->addSeparator();
    ptb->addAction(QPixmap(""), "Open Script", this, SLOT(slotNoImpl()));
    ptb->addAction(QPixmap(""), "Save Script", this, SLOT(slotNoImpl()));

    return ptb;
  }

public slots:
  void slotNoImpl() {
    QMessageBox::information(0, "Message", "Not implemented");
  }

private slots:

  void on_pbOpenScipt_clicked();
  void on_interfaceSaveSettings_clicked();
  void on_pbGenerateReport_clicked();
  void on_pbSaveScript_clicked();
  void on_pbStep_clicked();
  void on_pbTranslate_clicked();

  void on_pbRun_clicked();

private:
  Ui::AT_manager_client *ui;

};

#endif // AT_MANAGER_CLIENT_H
