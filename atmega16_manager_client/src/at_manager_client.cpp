  /**
  * Include libraries
  */
#include "at_manager_client.h"
#include "ui_at_manager_client.h"
#include "interpreter.h"
#include "at_thread.h"
#include "at_registers.h"
#include "at_report.h"
#include <QtGui>
#include <QRegExp>
#include "string.h"
#include <QTableView>
#include <QTreeView>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QThread>
#include <Windows.h>
#include "at_ftdi_module.h"
#include <QSettings>
#include "at_service_cmd.h"


QMap<QString, int> devMapNames;

  /**
  * Hack. Do timeout in main thread.
  * Func SLEEP use it
  */
#define HACK_SLEEP(time) \
          QEventLoop loop; \
          QTimer::singleShot( time, &loop, SLOT(quit()) ); \
          loop.exec() \


/**
  * When ATMC start, initilize uart, other interfaces
  * and attach to concrete named check box
  */
void AvrClientApp::interfaceInitilize() {
//  DWORD devIndex = 0; // первое устройство
//  char Buffer[64]; // резервируем место в памяти
//  FT_STATUS ftStatus;

//  AtInterfaceDescriptorTable device;

//  do {
//    ftStatus =
//    FT_ListDevices((PVOID)devIndex,Buffer,FT_LIST_BY_INDEX|FT_OPEN_BY_SERIAL_NUMBER);
//    if (ftStatus == FT_OK) {
//      // FT_ListDevices OK, серийный номер сохраняем в буфере

//      ui->comboBox->addItem(QString(Buffer));
//      ui->cb_uart1_test_interface->addItem(QString(Buffer));
//      ui->cb_uart2_test_interface->addItem(QString(Buffer));
//      ui->cb_uart3_test_interface->addItem(QString(Buffer));
//      ui->cb_uart4_test_interface->addItem(QString(Buffer));
//    }
//    else {

//      }
//      devIndex++;
//    }while (devIndex<100);

//  QSettings setting("home","atmc");

//  ui->le_uart1_test_interface->setText(setting.value("/Setting/Uart1Name","").toString());
//  ui->le_uart2_test_interface->setText(setting.value("/Setting/Uart2Name","").toString());
//  ui->le_uart3_test_interface->setText(setting.value("/Setting/Uart3Name","").toString());
//  ui->le_uart4_test_interface->setText(setting.value("/Setting/Uart4Name","").toString());

//  device.interfaceDescriptor = "";
//  device.interfaceDeviceName = "";
//  device.interfaceMajor = 0;
//  device.interfaceMinor = 0;
//  device.interfaceSpeed = 0;
//  FTDIDesciptorTable.dtFTDI.append(device);
}


/**
* Save interfaces setting
*/
void AvrClientApp::on_interfaceSaveSettings_clicked() {
//  QSettings setting("home","atmc");

//  setting.setValue("/Setting/DeviceName",ui->comboBox->currentText());

//  setting.setValue("/Setting/Uart1Name",ui->cb_uart1_test_interface->currentText());
//  ui->le_uart1_test_interface->setText( ui->cb_uart1_test_interface->currentText());
//  setting.setValue("/Setting/Uart2Name",ui->cb_uart2_test_interface->currentText());
//  ui->le_uart2_test_interface->setText( ui->cb_uart2_test_interface->currentText());
//  setting.setValue("/Setting/Uart3Name",ui->cb_uart3_test_interface->currentText());
//  ui->le_uart3_test_interface->setText( ui->cb_uart3_test_interface->currentText());
//  setting.setValue("/Setting/Uart4Name",ui->cb_uart4_test_interface->currentText());
//  ui->le_uart4_test_interface->setText( ui->cb_uart4_test_interface->currentText());
}



  /**
  * Constructor for ATMC application class.
  */
AvrClientApp::AvrClientApp(QWidget *parent) :
                   QMainWindow(parent), ui(new Ui::AT_manager_client) {
    ui->setupUi(this);

    // Button STEP set enable OFF
    ui->pbStep->setEnabled(false);

    // Add toolbar
    addToolBar(Qt::TopToolBarArea, createToolBar());

    // Init interfaces
    interfaceInitilize();

    //Init Report
    ATMC_Report* Report = ATMC_Report::Instance();

    //Fill command collection
    cmdCollection.addCommand(&iterAddCmd);
    cmdCollection.addCommand(&iterMovCmd);
    cmdCollection.addCommand(&iterCmpCmd);
    cmdCollection.addCommand(&iterOrCmd);
    cmdCollection.addCommand(&iterAndCmd);
    cmdCollection.addCommand(&iterJeCmd);
    cmdCollection.addCommand(&iterJmpCmd);
    cmdCollection.addCommand(&iterIncCmd);
    cmdCollection.addCommand(&iterDecCmd);
    cmdCollection.addCommand(&iterExitCmd);
    cmdCollection.addCommand(&iterPrintCmd);
    cmdCollection.addCommand(&iterSleepCmd);

    /**
      * Fill asociative array key(N) - value(Device)
      */
    devMapNames.insert("UART", 1);
    devMapNames.insert("CAN", 2);
    devMapNames.insert("SPI", 3);
    devMapNames["BTS"]   = 4;
    devMapNames["TIMER"] = 5;
    devMapNames["PORT"]  = 6;
}



/**
* Destructor for ATMC application class.
*/
AvrClientApp::~AvrClientApp()
{
    delete ui;
}


/**
  * Function repaint report
  */
void AvrClientApp::ATMC_reportTree_Repaint() {

  QStringList columns;
  columns << "Date Time" << "Device" << "Command" <<" Dump" << "Description" ;

  ui->treeWidget->setHeaderLabels(columns);
  ui->treeWidget->clear();

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  ui->treeWidget->insertTopLevelItems(0, Report->Repaint());
  ui->treeWidget->resizeColumnToContents(0);
  ui->treeWidget->resizeColumnToContents(1);
  ui->treeWidget->resizeColumnToContents(2);
  ui->treeWidget->resizeColumnToContents(3);

  ui->treeWidget->expandAll();
}


/**
  * Function refresh debug table
  */
void AvrClientApp::ATMC_debugTable_refresh() {
  ui->tableWidget->setColumnCount(8);
  ui->tableWidget->setRowCount(virtualDebbuger.cmdSequence.size());

  QTableWidgetItem *num_cmd         = NULL;
  QTableWidgetItem *label           = NULL;
  QTableWidgetItem *cmd_type        = NULL;
  QTableWidgetItem *goto_cmd        = NULL;
  QTableWidgetItem *dump            = NULL;
  QTableWidgetItem *op1             = NULL;
  QTableWidgetItem *op2             = NULL;
  QTableWidgetItem *link_edit_line  = NULL;

  QStringList lst;

  lst <<"#"<< "label" << "cmd_type" << "dump"<<"goto_cmd"<<"op1"<<"op2"<<"->";

  ui->tableWidget->setHorizontalHeaderLabels(lst);

  for ( int i = 0; i < virtualDebbuger.cmdSequence.size(); i++ ) {

    num_cmd         = new QTableWidgetItem(QString("%1").arg(virtualDebbuger.cmdSequence.at(i).num_cmd));
    label           = new QTableWidgetItem(QString("%1").arg(virtualDebbuger.cmdSequence.at(i).label));
    cmd_type        = new QTableWidgetItem(QString("%1").arg(virtualDebbuger.cmdSequence.at(i).cmd_type));
    dump            = new QTableWidgetItem(QString("%1").arg(virtualDebbuger.cmdSequence.at(i).dump));
    goto_cmd        = new QTableWidgetItem(QString("%1").arg(virtualDebbuger.cmdSequence.at(i).goto_cmd));
    op1             = new QTableWidgetItem(QString("%1").arg(virtualDebbuger.cmdSequence.at(i).op1));
    op2             = new QTableWidgetItem(QString("%1").arg(virtualDebbuger.cmdSequence.at(i).op2));
    link_edit_line  = new QTableWidgetItem(QString("%1").arg(virtualDebbuger.cmdSequence.at(i).link_edit_line));

    if ( virtualDebbuger.PC == i ) {
      num_cmd->setBackgroundColor(Qt::red);
      label->setBackground(Qt::red);
      cmd_type->setBackgroundColor(Qt::red);
      dump->setBackgroundColor(Qt::red);
      goto_cmd->setBackgroundColor(Qt::red);
      op1->setBackgroundColor(Qt::red);
      op2->setBackgroundColor(Qt::red);
      link_edit_line->setBackgroundColor(Qt::red);
    }

    ui->tableWidget->setItem(i,0, num_cmd);
    ui->tableWidget->setItem(i,1, label);
    ui->tableWidget->setItem(i,2, cmd_type);
    ui->tableWidget->setItem(i,3, dump);
    ui->tableWidget->setItem(i,4, goto_cmd);
    ui->tableWidget->setItem(i,5, op1);
    ui->tableWidget->setItem(i,6, op2);
    ui->tableWidget->setItem(i,7, link_edit_line);
  }

  ui->tableWidget->resizeColumnsToContents();
}


/**
  * Function refresh values of registers
  */
void AvrClientApp::ATMC_registers_Refresh() {
  int value;

  get_reg_value("FReg", &value);
  ui->lbFReg->setText(QString("%1").arg(value));

  get_reg_value("UReg1", &value);
  ui->lb_UReg1->setText(QString("%1").arg(value));
  get_reg_value("UReg2", &value);
  ui->lb_UReg2->setText(QString("%1").arg(value));
  get_reg_value("UReg3", &value);
  ui->lb_UReg3->setText(QString("%1").arg(value));
  get_reg_value("UReg4", &value);
  ui->lb_UReg4->setText(QString("%1").arg(value));
  get_reg_value("UReg5", &value);
  ui->lb_UReg5->setText(QString("%1").arg(value));
  get_reg_value("UReg6", &value);
  ui->lb_UReg6->setText(QString("%1").arg(value));
  get_reg_value("UReg7", &value);
  ui->lb_UReg7->setText(QString("%1").arg(value));
  get_reg_value("UReg8", &value);
  ui->lb_UReg8->setText(QString("%1").arg(value));

//  get_reg_value("UART1_SuR", &value);
//  ui->lb_UART1_SuR->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART2_SuR", &value);
//  ui->lb_UART2_SuR->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART3_SuR", &value);
//  ui->lb_UART3_SuR->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART4_SuR", &value);
//  ui->lb_UART4_SuR->setText(QString("0x%1").arg(value,8,16,QChar('0')));

//  get_reg_value("BTS_SuR", &value);
//  ui->lb_BTS_SuR->setText(QString("0x%1").arg(value,8,16,QChar('0')));

//  get_reg_value("UART1_CR", &value);
//  ui->lb_UART1_CR->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART2_CR", &value);
//  ui->lb_UART2_CR->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART3_CR", &value);
//  ui->lb_UART3_CR->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART4_CR", &value);
//  ui->lb_UART4_CR->setText(QString("0x%1").arg(value,8,16,QChar('0')));

//  get_reg_value("BTS_CR", &value);
//  ui->lb_BTS_CR->setText(QString("0x%1").arg(value,8,16,QChar('0')));

//  get_reg_value("UART1_SPEED", &value);
//  ui->lb_UART1_SPEED->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART2_SPEED", &value);
//  ui->lb_UART2_SPEED->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART3_SPEED", &value);
//  ui->lb_UART3_SPEED->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART4_SPEED", &value);
//  ui->lb_UART4_SPEED->setText(QString("%1").arg(QString::number(value,10)));


//  get_reg_value("UART1_CRC32_TX", &value);
//  ui->lb_UART1_CRC32_TX->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART1_CRC32_RX", &value);
//  ui->lb_UART1_CRC32_RX->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART1_SW_OV", &value);
//  ui->lb_UART1_SW_OV->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART1_HW_OV", &value);
//  ui->lb_UART1_HW_OV->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART1_HW_FE", &value);
//  ui->lb_UART1_HW_FE->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART1_HW_PE", &value);
//  ui->lb_UART1_HW_PE->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART1_TX_MSGS_LAST", &value);
//  ui->lb_UART1_TX_MSGS_LAST->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART1_RX_MSGS_LAST", &value);
//  ui->lb_UART1_RX_MSGS_LAST->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART1_TX_MSGS", &value);
//  ui->lb_UART1_TX_MSGS->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART1_RX_MSGS", &value);
//  ui->lb_UART1_RX_MSGS->setText(QString("%1").arg(QString::number(value,10)));

//  get_reg_value("UART2_CRC32_TX", &value);
//  ui->lb_UART2_CRC32_TX->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART2_CRC32_RX", &value);
//  ui->lb_UART2_CRC32_RX->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART2_SW_OV", &value);
//  ui->lb_UART2_SW_OV->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART2_HW_OV", &value);
//  ui->lb_UART2_HW_OV->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART2_HW_FE", &value);
//  ui->lb_UART2_HW_FE->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART2_HW_PE", &value);
//  ui->lb_UART2_HW_PE->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART2_TX_MSGS_LAST", &value);
//  ui->lb_UART2_TX_MSGS_LAST->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART2_RX_MSGS_LAST", &value);
//  ui->lb_UART2_RX_MSGS_LAST->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART2_TX_MSGS", &value);
//  ui->lb_UART2_TX_MSGS->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART2_RX_MSGS", &value);
//  ui->lb_UART2_RX_MSGS->setText(QString("%1").arg(QString::number(value,10)));

//  get_reg_value("UART3_CRC32_TX", &value);
//  ui->lb_UART3_CRC32_TX->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART3_CRC32_RX", &value);
//  ui->lb_UART3_CRC32_RX->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART3_SW_OV", &value);
//  ui->lb_UART3_SW_OV->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART3_HW_OV", &value);
//  ui->lb_UART3_HW_OV->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART3_HW_FE", &value);
//  ui->lb_UART3_HW_FE->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART3_HW_PE", &value);
//  ui->lb_UART3_HW_PE->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART3_TX_MSGS_LAST", &value);
//  ui->lb_UART3_TX_MSGS_LAST->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART3_RX_MSGS_LAST", &value);
//  ui->lb_UART3_RX_MSGS_LAST->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART3_TX_MSGS", &value);
//  ui->lb_UART3_TX_MSGS->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART3_RX_MSGS", &value);
//  ui->lb_UART3_RX_MSGS->setText(QString("%1").arg(QString::number(value,10)));

//  get_reg_value("UART4_CRC32_TX", &value);
//  ui->lb_UART4_CRC32_TX->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART4_CRC32_RX", &value);
//  ui->lb_UART4_CRC32_RX->setText(QString("0x%1").arg(value,8,16,QChar('0')));
//  get_reg_value("UART4_SW_OV", &value);
//  ui->lb_UART4_SW_OV->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART4_HW_OV", &value);
//  ui->lb_UART4_HW_OV->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART4_HW_FE", &value);
//  ui->lb_UART4_HW_FE->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART4_HW_PE", &value);
//  ui->lb_UART4_HW_PE->setText(QString("%1").arg(QString::number(value,16)));
//  get_reg_value("UART4_TX_MSGS_LAST", &value);
//  ui->lb_UART4_TX_MSGS_LAST->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART4_RX_MSGS_LAST", &value);
//  ui->lb_UART4_RX_MSGS_LAST->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART4_TX_MSGS", &value);
//  ui->lb_UART4_TX_MSGS->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART4_RX_MSGS", &value);
//  ui->lb_UART4_RX_MSGS->setText(QString("%1").arg(QString::number(value,10)));


//  get_reg_value("UART1_RX_BL", &value);
//  ui->lb_UART1_RX_BL->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART1_TX_BL", &value);
//  ui->lb_UART1_TX_BL->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART2_RX_BL", &value);
//  ui->lb_UART2_RX_BL->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART2_TX_BL", &value);
//  ui->lb_UART2_TX_BL->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART3_RX_BL", &value);
//  ui->lb_UART3_RX_BL->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART3_TX_BL", &value);
//  ui->lb_UART3_TX_BL->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART4_RX_BL", &value);
//  ui->lb_UART4_RX_BL->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("UART4_TX_BL", &value);
//  ui->lb_UART4_TX_BL->setText(QString("%1").arg(QString::number(value,10)));


//  get_reg_value("BTS_CFINT", &value);
//  ui->lb_BTS_CFINT->setText(QString("0x%1").arg(value,8,10,QChar('0')));
//  get_reg_value("BTS_CFEXT", &value);
//  ui->lb_BTS_CFEXT->setText(QString("0x%1").arg(value,8,10,QChar('0')));


//  get_reg_value("BTS_YEAR", &value);
//  ui->lb_BTS_YEAR->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("BTS_DAY", &value);
//  ui->lb_BTS_DAY->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("BTS_HOUR", &value);
//  ui->lb_BTS_HOUR->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("BTS_MINUTE", &value);
//  ui->lb_BTS_MINUTE->setText(QString("%1").arg(QString::number(value,10)));
//  get_reg_value("BTS_SECOND", &value);
//  ui->lb_BTS_SEC->setText(QString("%1").arg(QString::number(value,10)));
}

void AvrClientApp::ATMC_codeLineLight_Refresh( int popo )
{
  QList<QTextEdit::ExtraSelection> extraSelections;

  if (!ui->plainTextEdit->isReadOnly()) {
      QTextEdit::ExtraSelection selection;

      QPalette pal;
      QColor lineColor = pal.color(QPalette::Base).lighter(160);

      selection.format.setBackground(lineColor);
      selection.format.setProperty(QTextFormat::FullWidthSelection, true);
      int ggg =0;

      for ( int i = 0; i < popo; i++ )
        ggg+=ui->plainTextEdit->document()->findBlockByLineNumber(i).length();

      selection.cursor  = ui->plainTextEdit->textCursor();


      selection.cursor.setPosition(ggg);

      selection.cursor.clearSelection();
      extraSelections.append(selection);

    }
  ui->plainTextEdit->setExtraSelections(extraSelections);
  popo++;
}


  /**
  * TRANSLATE code script function
  */
void AvrClientApp::on_pbTranslate_clicked() {
  virtualDebbuger.cmdSequence.clear();
  ui->tableWidget->clear();
  ui->pbStep->setEnabled(true);
  clear_reg_value();

  AT_interpreter interpretator;

  int line_to_interpret = ui->plainTextEdit->document()->lineCount();
  for ( int i = 0; i < line_to_interpret; ++i ) {
    QTextBlock block = ui->plainTextEdit->document()->findBlockByLineNumber(i);
    QString context = block.text();
    interpretator.evaluate(context, i);
  }

  virtualDebbuger.PC = 0;
  ATMC_debugTable_refresh();
}


  /**
  * Is it code line PACKET or COMMAND ?
  */
bool at_is_packet(ATMC_obCodeLine current_exec_line) {
  if (current_exec_line.cmd_type == "PKT")
    return true;
  return false;
}


  /**
  * STEP by code function
  */
void AvrClientApp::on_pbStep_clicked() {

  int vdPC = virtualDebbuger.PC;

  if ( virtualDebbuger.PC >= virtualDebbuger.cmdSequence.size()-1 ) {
      ui->pbStep->setEnabled(false);
    }

  if ( cmdCollection.toPerform( virtualDebbuger.cmdSequence.at( vdPC ) ) ) {
      if ( virtualDebbuger.cmdSequence.at( vdPC ).dump == "SLEEP" ) {
          ui->pbStep->setEnabled(false);
          bool ok;
          HACK_SLEEP( virtualDebbuger.cmdSequence.at( vdPC ).op1.toInt(&ok,0) );
          ui->pbStep->setEnabled(true);
        }
      if ( ( virtualDebbuger.cmdSequence.at( vdPC ).dump != "JE" ) &&
           ( virtualDebbuger.cmdSequence.at( vdPC ).dump != "JMP" ) )
        virtualDebbuger.PC++;
      ATMC_debugTable_refresh();
      ATMC_registers_Refresh();
      ATMC_reportTree_Repaint();
      ATMC_codeLineLight_Refresh(virtualDebbuger.cmdSequence.at( vdPC ).link_edit_line);
      return;
    }


  if ( at_is_packet( virtualDebbuger.cmdSequence.at( vdPC ) ) ) {
    at_thread_state = at_send_command_packet;
    HACK_SLEEP(100);
    ATMC_debugTable_refresh();
    ATMC_registers_Refresh();
    ATMC_reportTree_Repaint();
    ATMC_codeLineLight_Refresh(virtualDebbuger.cmdSequence.at( vdPC ).link_edit_line);
    return;
  }
}


/* ========================================================================== */
/*                         Routines work with files                           */
/* ========================================================================== */


  /**
  * Open script
  */
void AvrClientApp::on_pbOpenScipt_clicked() {
  QString fname =
      QFileDialog::getOpenFileName(this, tr("Open input file"),
                                   "", tr("Text files(*.txt *.gen *.dat)"));
  if( !fname.isEmpty() ) {
    QFile file(fname);
    if ( !file.open(QIODevice::ReadOnly) ) {
      QMessageBox::information( this, tr("Cannot open input file!"), file.errorString() );
      return;
    }
    else {
      QTextStream out( &file );
      QString output = out.readAll();
      ui->plainTextEdit->setPlainText(output);
    }
  }
}


  /**
  * Generate Report
  */
void AvrClientApp::on_pbGenerateReport_clicked() {
  QFile file("report.html");
  if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    return;

  QTextStream out(&file);
  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  out << "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>";
  out << "<html xmlns='http://www.w3.org/1999/xhtml' dir='ltr' lang='ru-RU'>";
  out << "<head ><meta http-equiv='Content-Type' content='text/html; charset=UTF-8' />";
  out << "<title>ATMC report</title></head><body><table border='1'>";
  out << "<tr><td>Data and time</td><td>Command</td><td>Description</td><td>Dump</td></tr>";

  for ( int i = 0; i < Report->GetListSize(); i++ ) {
    out << "<tr><td>"  << Report->GetDataTime(i);
    out << "</td><td>" << Report->GetCommandName(i);
    out << "</td><td>" << Report->GetDescription(i);
    out << "</td><td>" << Report->GetDump(i);
    out << "</td></tr>";
  }

  out<<"</table></body></html>";
}


  /**
  * Save script
  */
void AvrClientApp::on_pbSaveScript_clicked() {
  QString fname =
      QFileDialog::getSaveFileName(this, tr("Save output file"),
                                   "", tr("gen files(*.gen)"));

  QFile file(fname);
  if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    return;

  QTextStream out(&file);

  out << ui->plainTextEdit->toPlainText();
}


void AvrClientApp::on_pbRun_clicked()
{

}
