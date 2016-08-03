#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QFileDialog>
#include <QTableWidgetItem>

#include <QDebug>

#include "initilizerappdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextCodec *langcodec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForTr      ( langcodec );
    QTextCodec::setCodecForCStrings( langcodec );
    QTextCodec::setCodecForLocale  ( langcodec );

    timer = new QTimer(this);



    connect( timer, SIGNAL(timeout()), this, SLOT(on_dsuActivUpdate()));

    QObject::connect( &appLogger, SIGNAL(updateSysLogger()), this, SLOT(systemLogRefresh()));
    QObject::connect( &appLogger, SIGNAL(updateProtoLogger()), this, SLOT(protoLogRefresh()));

    timer->start(1000);

    dsuProtocol.start();

    dsuRegs.DSUC->registerTableWidget( ui->dsucViewTable );
    dsuRegs.TTC->registerTableWidget( ui->ttcViewTable );
    dsuRegs.TBCTL->registerTableWidget( ui->tbctlViewTable );
    dsuRegs.BAD1->registerTableWidget( ui->bad1ViewTable );
    dsuRegs.BAD2->registerTableWidget( ui->bad2ViewTable );
    dsuRegs.BMA1->registerTableWidget( ui->bma1ViewTable );
    dsuRegs.BMA2->registerTableWidget( ui->bma2ViewTable );

    dsuRegs.DSUC->setItemsToTableWidget();
    dsuRegs.TTC->setItemsToTableWidget();
    dsuRegs.TBCTL->setItemsToTableWidget();
    dsuRegs.BAD1->setItemsToTableWidget();
    dsuRegs.BAD2->setItemsToTableWidget();
    dsuRegs.BMA1->setItemsToTableWidget();
    dsuRegs.BMA2->setItemsToTableWidget();

    traceBufferViewInit();
}

MainWindow::~MainWindow() {
  delete ui;
}


/**
  *
  */
void MainWindow::on_deviceBrowserButton_clicked() {
  /* Инициализация устройств */
  DWORD   nums;
  QString serialNum;

  ui->deviceListBox->clear();

  ftdiPort.showPorts( 0, &nums, &serialNum );

  for ( DWORD i = 0; i < nums; i++ ) {
    ftdiPort.showPorts( i, &nums, &serialNum );
    ui->deviceListBox->addItem( serialNum );
  }
}

/**
  *
  */
void MainWindow::on_deviceListBox_currentIndexChanged(int index) {
  DWORD nums;
  QString serialNum;
  ui->deviceInfoLabel->setText( ftdiPort.showPorts( index, &nums, &serialNum ) );
}

/**
  *
  */
void MainWindow::on_dsuEnableBox_clicked() {

}

/**
  *TODO:
  */
void MainWindow::on_dsuActivUpdate() {

  unsigned char portData = ftdiPort.readFromPortB(false) ;
  ui->dsuEnableBox->setChecked( portData & 0x8 );
  ui->dsuBreakBox->setChecked( portData & 0x4 );
  ui->dsuActiveBox->setChecked( portData & 0x1 );

}

/**
  *
  */
void MainWindow::on_dsuBreakBox_clicked() {

}

/**
  * Записать данные в память
  */
void MainWindow::on_wmemButton_clicked() {
  bool ok;
  dsuProtocol.wmem( ui->addrWmemCmdEdit->text().toUInt(&ok, 16),
                    ui->dataWmemCmdEdit->text().toUInt(&ok, 16) );
}

/**
  * Считать данные из памяти
  */
void MainWindow::on_memButton_clicked() {
  bool ok;
  char *data;
  data = dsuProtocol.mem( ui->addrMemCmdEdit->text().toUInt(&ok, 16),
                          ui->dataCountMemCmdEdit->text().toUInt(&ok, 10));
}

/**
  * Обновить системный журнал
  */
void MainWindow::systemLogRefresh() {

  QString st;

  st = appLogger.getNotViewedMsg( appLogger.SYSTEM_LOGGER );

  while ( st != "endSearchByLogger" ) {
    ui->systemLogView->append( st );
    st = appLogger.getNotViewedMsg( appLogger.SYSTEM_LOGGER );
  }

}


/**
  * Обновить журнал протокола взаимодействия
  */
void MainWindow::protoLogRefresh() {
  QString st;

  st = appLogger.getNotViewedMsg( appLogger.PROTOCOL_LOGGER );

  while ( st != "endSearchByLogger" ) {
    ui->protocolLogView->appendPlainText( st );
    st = appLogger.getNotViewedMsg( appLogger.PROTOCOL_LOGGER );
  }
}

/**
  * Выбор файла образа
  */
void MainWindow::on_fileBrowserEELoadButton_clicked() {
  QString fileName = QFileDialog::getOpenFileName( this, tr("Открыть образ"),
                                                   "/home",
                                                   tr("files (*.* *.elf *.m4)") );

  ui->fpathEEloadEdit->setText( fileName );
}

/**
  * Записать образ в память
  */
void MainWindow::on_eeloadButton_clicked() {
  if ( ui->fpathEEloadEdit->text() == "" ) {
     appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE, " Файл не выбран", appLogger.SYSTEM_LOGGER );
    return;
  }
}

/**
  *
  */
void MainWindow::on_dsuEnableBox_toggled(bool checked) {
  appLogger.sendDataToViewer(  appLogger.INFO_MSG_TYPE, " Включение DSU " , appLogger.SYSTEM_LOGGER );

  unsigned char portData = 0;

  if ( checked ) {
    portData = ftdiPort.readFromPortB(false) | 0x8;
    ftdiPort.writeToPortB( portData );
  }
  else {
    portData = ftdiPort.readFromPortB(false) & 0xF7;
    ftdiPort.writeToPortB( portData );
  }

}

/**
  *
  */
void MainWindow::on_dsuBreakBox_toggled(bool checked) {
  appLogger.sendDataToViewer(  appLogger.INFO_MSG_TYPE, " DSU break" , appLogger.SYSTEM_LOGGER );

   unsigned char portData = 0;

    if ( checked ) {
        portData = ftdiPort.readFromPortB(false) | 0x4;
        ftdiPort.writeToPortB( portData );
    }
    else {
        portData = ftdiPort.readFromPortB(false) & 0xFB;
        ftdiPort.writeToPortB( portData );
    }
}

/**
  *
  */
void MainWindow::on_startPortAButton_clicked() {
  if ( ftdiPort.Initialization()==0 /*succesfull*/) {
    ui->startPortAButton->setEnabled( false );
    ui->stopPortAButton->setEnabled( true );
  }
}

/**
  *
  */
void MainWindow::on_stopPortAButton_clicked() {
  ftdiPort.closeDSUSession();
  ui->startPortAButton->setEnabled( true );
  ui->stopPortAButton->setEnabled( false );
}

/**
  *
  */
void MainWindow::on_dsuRegsUpdateButton_clicked() {
//  bool ok;
//  char *data;
//  data = dsuProtocol.mem( ui->addrMemCmdEdit->text().toUInt(&ok, 16),
//                          ui->dataCountMemCmdEdit->text().toUInt(&ok, 10));

  dsuRegs.DSUC->refresh();
  dsuRegs.TBCTL->refresh();
  dsuRegs.TTC->refresh();
  dsuRegs.BAD1->refresh();
  dsuRegs.BAD2->refresh();
  dsuRegs.BMA1->refresh();
  dsuRegs.BMA2->refresh();
  traceBufferViewRefresh();
}

/**
  *
  */
void MainWindow::on_dsucViewTable_cellPressed(int row, int column) {

}
/**
  *
  */
void MainWindow::on_dsucViewTable_cellEntered(int row, int column) {

}

/**
  *
  */
void MainWindow::on_dsucViewTable_cellChanged( int row, int column ) {
  bool ok;
  dsuRegs.DSUC->setDataViewColumn(
        ui->dsucViewTable->item( row, column )->text().toInt( &ok, 16 ),
        column );
}
/**
  *
  */
void MainWindow::on_tbctlViewTable_cellChanged(int row, int column) {
  bool ok;
  dsuRegs.TBCTL->setDataViewColumn(
        ui->tbctlViewTable->item( row, column )->text().toInt( &ok, 16 ),
        column );
}
/**
  *
  */
void MainWindow::on_ttcViewTable_cellChanged(int row, int column) {
  bool ok;
  dsuRegs.TTC->setDataViewColumn(
        ui->ttcViewTable->item( row, column )->text().toInt( &ok, 16 ),
        column );
}
/**
  *
  */
void MainWindow::on_bad1ViewTable_cellChanged(int row, int column) {
  bool ok;
  dsuRegs.BAD1->setDataViewColumn(
        ui->bad1ViewTable->item( row, column )->text().toInt( &ok, 16 ),
        column );
}
/**
  *
  */
void MainWindow::on_bad2ViewTable_cellChanged(int row, int column) {
  bool ok;
  dsuRegs.BAD2->setDataViewColumn(
        ui->bad2ViewTable->item( row, column )->text().toInt( &ok, 16 ),
        column );
}
/**
  *
  */
void MainWindow::on_bma1ViewTable_cellChanged(int row, int column) {
  bool ok;
  dsuRegs.BMA1->setDataViewColumn(
        ui->bma1ViewTable->item( row, column )->text().toInt( &ok, 16 ),
        column );
}
/**
  *
  */
void MainWindow::on_bma2ViewTable_cellChanged(int row, int column) {
  bool ok;
  dsuRegs.BMA2->setDataViewColumn(
        ui->bma2ViewTable->item( row, column )->text().toInt( &ok, 16 ),
        column );
}


/**
  *
  */
void MainWindow::traceBufferViewInit() {
  ui->traceBufferView->setColumnCount( 8 ); /* количество полей */
  ui->traceBufferView->setRowCount( 1024 ); /* количество записей */

  opcode    = NULL;
  errorMode = NULL;
  intrTrap  = NULL;
  pc        = NULL;
  ldStParam = NULL;
  ttc       = NULL;
  mci       = NULL;
  ibh       = NULL;

  QStringList lst;
  lst <<"opcode"<< "errorMode" << "intrTrap" << "pc"<<"ldStParam"<<"ttc"<<"mci"<<"ibh";
  ui->traceBufferView->setHorizontalHeaderLabels(lst);

  for ( int i = 0; i < 1024; i++ ) {
    opcode      = new QTableWidgetItem("");
    errorMode   = new QTableWidgetItem("");
    intrTrap    = new QTableWidgetItem("");
    pc          = new QTableWidgetItem("");
    ldStParam   = new QTableWidgetItem("");
    ttc         = new QTableWidgetItem("");
    mci         = new QTableWidgetItem("");
    ibh         = new QTableWidgetItem("");
  }
}

/**
  *
  */
void MainWindow::traceBufferViewRefresh() {

  for ( int i = 0; i < 8; i++ ) {
    ui->traceBufferView->item( dsuRegs.TBCTL->getIcnt(), i )->setBackgroundColor( Qt::red );
  }

  ui->traceBufferView->item( dsuRegs.TBCTL->getIcnt(), 0 )->setText("opcode");
  ui->traceBufferView->item( dsuRegs.TBCTL->getIcnt(), 0 )->setText("errorMode");
  ui->traceBufferView->item( dsuRegs.TBCTL->getIcnt(), 0 )->setText("intrTrap");
  ui->traceBufferView->item( dsuRegs.TBCTL->getIcnt(), 0 )->setText("pc");
  ui->traceBufferView->item( dsuRegs.TBCTL->getIcnt(), 0 )->setText("ldStParam");
  ui->traceBufferView->item( dsuRegs.TBCTL->getIcnt(), 0 )->setText("ttc");
  ui->traceBufferView->item( dsuRegs.TBCTL->getIcnt(), 0 )->setText("mci");
  ui->traceBufferView->item( dsuRegs.TBCTL->getIcnt(), 0 )->setText("ibh");

  ui->traceBufferView->resizeColumnsToContents();

}
