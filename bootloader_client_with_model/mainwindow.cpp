#include "mainwindow.h"
#include "ui_mainwindow.h"

QTimer *timer;

QHash<int, QString> statesCodes;
QHash<int, QString> operationCodes;
QHash<int, QString> abonCodes;

QWaitCondition          waitCond;
ECI_CTRL_MESSAGE        telemetryData;
int                     lastState = -1;
quint8                  canPackData[8];
int                     sizeSendPacketsQuery       = 0;
int                     writeOrEraseWriteOperation = 0;



//InterfaceStrategy *InteractInterface;

#include <QUrl>

void initBootloaderStates() {
    statesCodes[0] = "BOOTLOADER_SUCCESSFUL";

    statesCodes[0x80]                   = "BOOTLOADER_ERROR";
    statesCodes[(BOOTLOADER_ERROR + 0)] = "BOOTLOADER_UNKNOWN_ERROR";
    statesCodes[(BOOTLOADER_ERROR + 1)] = "BOOTLOADER_BUFFER_FULL";
    statesCodes[(BOOTLOADER_ERROR + 2)] = "BOOTLOADER_ADDRESS_INCORRECT";
    statesCodes[(BOOTLOADER_ERROR + 3)] = "BOOTLOADER_ARRAY_COUNT_INCORRECT";
    statesCodes[1]                      = "BOOTLOADER_ARRAY_RECEIVING";
    statesCodes[(BOOTLOADER_ERROR + 4)] = "BOOTLOADER_ARRAY_INDEX_INCORRECT";
    statesCodes[(BOOTLOADER_ERROR + 5)] = "BOOTLOADER_ARRAY_RECEIVE_FAILED";
    statesCodes[2]                      = "BOOTLOADER_ARRAY_BUFFER_VERIFYING";
    statesCodes[(BOOTLOADER_ERROR + 6)] = "BOOTLOADER_ARRAY_BUFFER_VERIFY_FAILED";
    statesCodes[3]                      = "BOOTLOADER_WRITING";
    statesCodes[4]                      = "BOOTLOADER_WRITE_VERIFYING";
    statesCodes[(BOOTLOADER_ERROR + 7)] = "BOOTLOADER_WRITE_VERIFY_FAILED";
    statesCodes[5]                      = "BOOTLOADER_ERASING";
    statesCodes[6]                      = "BOOTLOADER_CLEAN_VERIFYING";
    statesCodes[(BOOTLOADER_ERROR + 9)] = "BOOTLOADER_CLEAN_VERIFY_FAILED";
    statesCodes[7]                          = "BOOTLOADER_ERASE_VERIFYING";
    statesCodes[(BOOTLOADER_ERROR + 10)]    = "BOOTLOADER_ERASE_VERIFY_FAILED";
    statesCodes[8]                          = "BOOTLOADER_IMAGE_VERIFYING";
    statesCodes[(BOOTLOADER_ERROR + 11)]    = "BOOTLOADER_IMAGE_VERIFY_FAILED";
    statesCodes[(BOOTLOADER_ERROR + 12)]    = "BOOTLOADER_IMAGE_NOT_FOUND";
    statesCodes[(BOOTLOADER_ERROR + 13)]    = "BOOTLOADER_IMAGE_NOT_SUPPORTED";
    statesCodes[9]                          = "BOOTLOADER_FULL_IMAGE_VERIFYING";
    statesCodes[(BOOTLOADER_ERROR + 14)]    = "BOOTLOADER_FULL_IMAGE_VERIFYING_FAILED";
    statesCodes[10]                         = "BOOTLOADER_ST_PENDING";
return;
}


void initBootloaderOpcodes(){
    operationCodes[PROTO_OP_ENTER_BOOTLOADER]   = "PROTO_OP_ENTER_BOOTLOADER";
    operationCodes[PROTO_OP_WRITE]              = "PROTO_OP_WRITE";
    operationCodes[PROTO_OP_ERASE_AND_WRITE]    = "PROTO_OP_ERASE_AND_WRITE";
    operationCodes[PROTO_OP_SET_ACTIVE_IMAGE]   = "PROTO_OP_SET_ACTIVE_IMAGE";
    operationCodes[PROTO_OP_LOAD_IMAGE]         = "PROTO_OP_LOAD_IMAGE";
    operationCodes[PROTO_OP_VERIFY_IMAGE]       = "PROTO_OP_VERIFY_IMAGE";
    operationCodes[PROTO_OP_ERASE_AREA]         = "PROTO_OP_ERASE_AREA";
    operationCodes[PROTO_OP_TELEMETRY]          = "PROTO_OP_TELEMETRY";
return;
}


void initBootloaderAbonCodes() {
    abonCodes[SENDER_ADDR]      =   "OBC";
    abonCodes[RECEIVER_ADDR]    =   "Client`s Software";
}

/**
  * ctor mainwindow
  */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_model     = new model(this);
    proxyModel  = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(m_model);
    proxyModel->setFilterRegExp(".*");
    ui->tableView->setModel(proxyModel);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_3_clicked()));
    timer->start(3000);

    QUrl url;
    url.setPath("index.html");
    ui->texttextBrowserBrowser->setSource(url);

    on_loadCsvButton_clicked();

    QObject::connect( &cmdLog, SIGNAL(doIt()), this, SLOT(refresh_log()) );
    QObject::connect( &telemetryLog, SIGNAL(doIt()), this, SLOT(refresh_telemetry()) );
    QObject::connect( &sPacketsBar, SIGNAL(doIt()), this, SLOT(refresh_sendPacketsBar()) );

    ui->eightByteIndicator0->setText("XX"); ui->eightByteIndicator1->setText("XX"); ui->eightByteIndicator2->setText("XX");
    ui->sevenByteIndicator0->setText("XX"); ui->sevenByteIndicator1->setText("XX"); ui->sevenByteIndicator2->setText("XX");
    ui->sixByteIndicator0->setText("XX");   ui->sixByteIndicator1->setText("XX");   ui->sixByteIndicator2->setText("XX");
    ui->fiveByteIndicator0->setText("XX");  ui->fiveByteIndicator1->setText("XX");  ui->fiveByteIndicator2->setText("XX");
    ui->fourByteIndicator0->setText("XX");  ui->fourByteIndicator1->setText("XX");  ui->fourByteIndicator2->setText("XX");
    ui->threeByteIndicator0->setText("XX"); ui->threeByteIndicator1->setText("XX"); ui->threeByteIndicator2->setText("XX");
    ui->twoByteIndicator0->setText("XX");   ui->twoByteIndicator1->setText("XX");   ui->twoByteIndicator2->setText("XX");
    ui->oneByteIndicator0->setText("XX");   ui->oneByteIndicator1->setText("XX");   ui->oneByteIndicator2->setText("XX");


    initBootloaderStates();
    initBootloaderOpcodes();
    initBootloaderAbonCodes();

    ui->sendPacketsBar->setRange( 0, 100 );
    ui->sendPacketsBar->setValue( 0 );

    QFile file("data.csv");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << " \"TIME\", \"TRAFFIC TYPE\",\"COMMAND NAME\",\"ABONENT RECEIVER\",\"ABONENT SENDER\",\"ATTR\",\"DATA\"";
    file.close();


}



#include <QMutex>

QMutex mut2;

void MainWindow::addEventToView()
{
mut2.lock();
    QStringList rec, tebl;


    while (!dataExtractor.oneRecord.isEmpty()) {
        rec = dataExtractor.oneRecord.takeFirst();
        m_model->insertRows(0/* ui->tableView->selectionModel()->currentIndex().row()*/, 1, rec );
    }
mut2.unlock();

}

/**
  * dtor mainwindow
  */
MainWindow::~MainWindow()
{
    delete ui;
}


/**
  * Refresh log
  */
void MainWindow::refresh_log()
{
    ui->pteActionsLog->clear();
    for ( int i = 0; i < cmdLog._log.size(); i++ ) {
        ui->pteActionsLog->appendPlainText((cmdLog._log.at(i)));
    }
}

/**
  * Refresh telemetry
  */
void MainWindow::refresh_telemetry()
{

    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForCStrings(codec);
    ui->telemetryEdit->clear();
    for ( int i = 0; i < telemetryLog._log.size(); i++ ) {
        ui->telemetryEdit->appendPlainText((telemetryLog._log.at(i)));
    }

    hican_canid_t hiCanId;
    hiCanId.value  = telemetryData.u.sCanMessage.u.V0.dwMsgId;

    ui->senderAddrIndicator->setText(QString("0x%1").arg(hiCanId.field.saddr,0,16));
    ui->receiverAddrIndicator->setText(QString("0x%1").arg(hiCanId.field.raddr,0,16));
    ui->attrIndicator->setText(QString("0x%1").arg(0,0,16));
    ui->typeIndicator->setText(QString("0x%1").arg(hiCanId.field.code,0,16));

    if (((hiCanId.field.b7 == 1) and (hiCanId.field.b6 == 1) )) {
        for ( int i = 0; i < telemetryData.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc; i++ ) {
            if (i == 0 ) ui->eightByteIndicator1->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 1 ) {
                ui->sevenByteIndicator1->setText(QString("0x%1 ( %2 )").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16).arg(
                                                     statesCodes[telemetryData.u.sCanMessage.u.V0.abData[i]]));
                lastState       = telemetryData.u.sCanMessage.u.V0.abData[i];

//                ui->gbCheckCRC->setEnabled(true);
//                ui->gbOpenImage->setEnabled(true);
//                ui->gbWriteToFlash->setEnabled(true);
//                ui->gbClearFlash->setEnabled(true);
//                ui->gbClearFlash_2->setEnabled(true);
//                ui->pbClearRAMBuffer->setEnabled(true);
            }
            if (i == 2 ) ui->sixByteIndicator1->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 3 ) ui->fiveByteIndicator1->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 4 ) ui->fourByteIndicator1->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 5 ) ui->threeByteIndicator1->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 6 ) ui->twoByteIndicator1->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 7 ) ui->oneByteIndicator1->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
        }
    }
    else {
        for ( int i = 0; i < telemetryData.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc; i++ ) {
            if (i == 0 ) ui->eightByteIndicator0->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 1 ) ui->sevenByteIndicator0->setText(QString("0x%1 ").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 2 ) ui->sixByteIndicator0->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 3 ) ui->fiveByteIndicator0->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 4 ) ui->fourByteIndicator0->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 5 ) ui->threeByteIndicator0->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 6 ) ui->twoByteIndicator0->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
            if (i == 7 ) ui->oneByteIndicator0->setText(QString("0x%1").arg(telemetryData.u.sCanMessage.u.V0.abData[i],0,16));
        }
    }

}

/**
  * Refresh statusBar
  */
void MainWindow::refresh_sendPacketsBar()
{
    ui->sendPacketsBar->setValue( (100 * ( sizeSendPacketsQuery - sendPacksQuery.size())) / sizeSendPacketsQuery );
}


/**
  * Fill Can Id
  */
unsigned int CanIdFill( int msgType, int AO,
                        int AP,      int b7,
                        int b6,      int b5,
                        int b4,      int ExtCmd,
                        int opcode) {
    CanIdStruct id;

    id.value = 0;

    id.flags.msgType            = msgType;
    id.flags.AO                 = AO;
    id.flags.AP                 = AP;
    id.flags.b7                 = b7;
    id.flags.b6                 = b6;
    id.flags.b5                 = b5;
    id.flags.b4                 = b4;
    id.flags.extCmd             = ExtCmd;
    id.flags.opcode             = opcode;

    return id.value;
}


/**
  * Create can packet to send
  */
void createCanPacket(int id, int len, quint8 *buf, bool show) {

    ECI_CTRL_MESSAGE pack;


    if ( !isDataTypeOfMsg ) cmdLog.add(" ");
    if ( !isDataTypeOfMsg ) cmdLog.add(" Create command ... " );
    if ( !isDataTypeOfMsg ) cmdLog.add(" - CAN packet content: " );
    if ( !isDataTypeOfMsg ) cmdLog.add(QString(" - Id  =  0x%1 ").arg(id,0,16) );
    if ( !isDataTypeOfMsg ) cmdLog.add(QString(" - Data length =  %1").arg(len) );


    pack.wCtrlClass                             = 0;
    pack.u.sCanMessage.dwVer                    = 0;

    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.afc   = 0;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc   = 0;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.ext   = 0;

    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.hpm   = 0;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.ovr   = 0;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.res   = 0;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.rtr   = 0;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.srr   = 0;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.ssm   = 0;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.type  = 0;


    pack.u.sCanMessage.u.V0.dwMsgId            = 0;


    for ( int i = 0; i < len; i++ )
        pack.u.sCanMessage.u.V0.abData[i] = 0;

    pack.wCtrlClass                            = ECI_CTRL_CAN;
    pack.u.sCanMessage.dwVer                   = ECI_STRUCT_VERSION_V0;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.ext  = 1;
    pack.u.sCanMessage.u.V0.dwMsgId            = (DWORD)id;
    pack.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc  = len;

    QString data=" - Data: ";
    for ( int i = 0; i < len; i++ ) {
        pack.u.sCanMessage.u.V0.abData[i] = buf[i];
        data+= QString("%1").arg(buf[i],0,16) + " ";
    }

    sendMsgArray     packToArray;

    packToArray.show    = show;
    packToArray.msg     = pack;

    if ( !isDataTypeOfMsg ) { // command
        sendPacksQuery.prepend(packToArray);
    }
    else {
        sendPacksQuery.append(packToArray);
    }

    if ( !isDataTypeOfMsg ) cmdLog.add( data );
}


/**
  * Open image file and parse it by MD
  */
void MainWindow::on_pbOpenImageFile_clicked() {
    quint8              data;
    int                 currPosX, currPosY;

    doperations.init();

    QString tmp = QDir::currentPath();
    QFile fil("imgpath.txt");
    if( fil.open( QIODevice::ReadOnly ) ) {
        QDataStream stream(&fil);
        stream.setVersion (QDataStream::Qt_4_2) ;
        stream >> tmp;
        fil.close();
    }

    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("open File"),
                tmp,
                tr("txt Files (*.img)") );

    QFile file(fileName);
    if( file.open( QIODevice::ReadOnly ) ) {
        cmdLog.add(" " );
        cmdLog.add(" Was opened file " + fileName);
        QDataStream stream(&file);
        stream.setVersion (QDataStream::Qt_4_2) ;
        while ( !file.atEnd() ) {
            stream >> data;
            doperations.getCurrentPosXY(&currPosX, &currPosY);
            doperations.fillMdQueue( data );
        }

        if( stream.status() != QDataStream::Ok ) {
            cmdLog.add("Error reading file");
            cmdLog.refresh();
        }
        file.close();
    }

//    QFile file1(QString("/home/petrov/out300kb.txt"));
//    if( file1.open( QIODevice::WriteOnly ) ) {
//        QDataStream stream(&file1);
//        stream.setVersion (QDataStream::Qt_4_2) ;
//        for ( quint32 i = 0; i <= 50*1024; i++)
//            stream << i;

//        file1.close();
//    }

    doperations.fillMdCrc32();

    if ( currPosY < MD_SIZE) {
        cmdLog.add(QString("all full data arrays is %1 ").arg(currPosX,0,10));
        cmdLog.add(QString("And 1 appendix data array"));
    }

    int i;

    for ( i = 0; i < currPosX ;i++ ) {
        cmdLog.add(QString(" num array = %1; crc32 = 0x%2; block_size = %3").arg(i,0,10).arg(doperations._mdCrc32[i],0,16).arg(MD_SIZE,0,10));
    }
    cmdLog.add(QString(" num array = %1; crc32 = 0x%2; block_size = %3").arg(i,0,10).arg(doperations._mdCrc32[i],0,16).arg(doperations._currentPosY,0,10));

    cmdLog.refresh();
    if (fileName !="") {
    ui->pathLineEdit->setText(fileName);


    if( fil.open( QIODevice::WriteOnly ) ) {
        QDataStream stream(&fil);
        stream.setVersion (QDataStream::Qt_4_2) ;       
        stream <<  QFileInfo(fileName).absolutePath();    
        file.close();
    }

    }
}


/**
  * Enter to bootloader
  */
void MainWindow::on_pbEnterBootloader_clicked()
{
    quint8          *canPackData = NULL;

    isDataTypeOfMsg              = false;

    int isNeedAck;
    if  ( ui->reqAckBox->checkState() ) {
        isNeedAck=HICAN_CMD_PKT_WITH_ACK;
    }
    else {
        isNeedAck=HICAN_CMD_PKT_WITHOUT_ACK;
    }

    createCanPacket( CanIdFill( 0, RECEIVER_ADDR, SENDER_ADDR, HICAN_CMD_PKT, isNeedAck, HICAN_CMD_PKT_WITHOUT_PARAMS,
                               0, 0, PROTO_OP_ENTER_BOOTLOADER), 0, canPackData, true );

    sizeSendPacketsQuery =  sendPacksQuery.size();

    cmdThreadState = kSendCommand;

    prACK = true;
}

/**
  * Load image
  */
void MainWindow::on_pbClearRAMBuffer_clicked()
{
    quint8          *canPackData = NULL;

    isDataTypeOfMsg = false;

    int isNeedAck;
    if  ( ui->reqAckBox->checkState() ) {
        isNeedAck=HICAN_CMD_PKT_WITH_ACK;
    }
    else {
        isNeedAck=HICAN_CMD_PKT_WITHOUT_ACK;
    }
    createCanPacket( CanIdFill( 0, RECEIVER_ADDR, SENDER_ADDR, HICAN_CMD_PKT, isNeedAck, HICAN_CMD_PKT_WITHOUT_PARAMS,
                                0, 0, PROTO_OP_LOAD_IMAGE ), 0, canPackData, true );

    cmdThreadState = kSendCommand;

    sizeSendPacketsQuery =  sendPacksQuery.size();

    prACK = true;
}



/**
  * Clear memory area
  */
void MainWindow::on_pbClearFlash_clicked()
{
    bool             ok;
    quint8           canPackData[8];

    isDataTypeOfMsg = false;

    quint32 addr = ui->addrCmEdit->text().toInt(&ok,16);
    addr /=64*1024;

    canPackData[0] = (BYTE)(addr );
    canPackData[1] = (BYTE)(addr >> 8);

    quint8 len = ui->blockCountCmEdit->text().toInt(&ok,16);
    canPackData[2] = (BYTE)( len );


    int isNeedAck;
    if  ( ui->reqAckBox->checkState() ) {
        isNeedAck=HICAN_CMD_PKT_WITH_ACK;
    }
    else {
        isNeedAck=HICAN_CMD_PKT_WITHOUT_ACK;
    }
    createCanPacket( CanIdFill( 0, RECEIVER_ADDR, SENDER_ADDR, HICAN_CMD_PKT, isNeedAck, HICAN_CMD_PKT_WITH_PARAMS,
                                0, 0, PROTO_OP_ERASE_AREA ), 3, canPackData, true  );

    cmdThreadState = kSendCommand;

    sizeSendPacketsQuery =  sendPacksQuery.size();

    prACK = true;
}


/**
  * Write data
  */
void MainWindow::on_pbWriteToFlash_clicked()
{
    bool ok;

    if ((ui->leSetParamStartAddr->text() != "" ) &&
            ((doperations._currentPosY != 0 )||(doperations._currentPosX != 0))) {

        quint32 addr = ui->leSetParamStartAddr->text().toInt(&ok,16);
        addr /=64*1024;

        canPackData[0] = (BYTE)(addr);
        canPackData[1] = (BYTE)(addr >> 8);

        dataThreadState = kWaitCompleteOperation;
        isDataTypeOfMsg = true;

        if ( !ui->clearCheck->isChecked() ) {
            writeOrEraseWriteOperation = 8;
        }
        else {
            writeOrEraseWriteOperation = 7;
        }
    }
    else {
        return;
    }
}


/**
  * Verify data of mem area
  */
void MainWindow::on_VerifyButton_clicked() {
    bool             ok;
    quint8           canPackData[8];

    isDataTypeOfMsg = false;

    quint32 addr = ui->VerifyEdit->text().toInt(&ok,16);
    addr /=64*1024;

    canPackData[0] = (BYTE)(addr );
    canPackData[1] = (BYTE)(addr >> 8);


    int isNeedAck;
    if  ( ui->reqAckBox->checkState() ) {
        isNeedAck=HICAN_CMD_PKT_WITH_ACK;
    }
    else {
        isNeedAck=HICAN_CMD_PKT_WITHOUT_ACK;
    }
    createCanPacket( CanIdFill( 0, RECEIVER_ADDR, SENDER_ADDR, HICAN_CMD_PKT, isNeedAck, HICAN_CMD_PKT_WITH_PARAMS,
                                0, 0, PROTO_OP_VERIFY_IMAGE ), 2, canPackData, true  );

    sizeSendPacketsQuery =  sendPacksQuery.size();

    cmdThreadState = kSendCommand;
    prACK = true;
    qDebug()<<"po";

}

/**
  * Set active image
  */
void MainWindow::on_setActiveButton_clicked() {
    bool             ok;
    quint8           canPackData[8];

    isDataTypeOfMsg = false;

    quint32 addr = ui->setActiveEdit->text().toInt(&ok,16);
    addr /=64*1024;

    canPackData[0] = (BYTE)(addr);
    canPackData[1] = (BYTE)(addr >> 8);


    int isNeedAck;
    if  ( ui->reqAckBox->checkState() ) {
        isNeedAck=HICAN_CMD_PKT_WITH_ACK;
    }
    else {
        isNeedAck=HICAN_CMD_PKT_WITHOUT_ACK;
    }

    createCanPacket( CanIdFill( 0, RECEIVER_ADDR, SENDER_ADDR, HICAN_CMD_PKT, isNeedAck, HICAN_CMD_PKT_WITH_PARAMS,
                                0, 0, PROTO_OP_SET_ACTIVE_IMAGE ), 2, canPackData, true  );

    cmdThreadState = kSendCommand;
    prACK = true;

    sizeSendPacketsQuery =  sendPacksQuery.size();
}


/**
  * Фильтрация модели
  */
void MainWindow::on_pushButton_clicked()
{  
//    proxyModel->setFilterKeyColumn(1); // traffic type

//    //  proxyModel->setFilterFixedString("5");

//    if ( ui->packTypeBox->currentText() == "Фильтровать телеметрию" ) {
//        proxyModel->setFilterRegExp(QRegExp("telemetry", Qt::CaseInsensitive, QRegExp::FixedString));
//    }

//    if ( ui->packTypeBox->currentText() == "Фильтровать команды" ) {
//        proxyModel->setFilterRegExp(QRegExp("cmd", Qt::CaseInsensitive, QRegExp::FixedString));
//    }

//    if ( ui->packTypeBox->currentText() == "Фильтровать квитанции" ) {
//        proxyModel->setFilterRegExp(QRegExp("ack", Qt::CaseInsensitive, QRegExp::FixedString));
//    }

//      proxyModel->invalidate(); // аннулирует текущий вид и заново его перестраивает
}

void MainWindow::setViewForm()
{

    connect(&cmdLog, SIGNAL(doIt()), this, SLOT(addEventToView()) );
    connect(&telemetryLog, SIGNAL(doIt()), this, SLOT(addEventToView()) );
}

void MainWindow::on_loadCsvButton_clicked()
{
      m_model->loadData("data.csv");
}

void MainWindow::on_saveCsvButton_clicked()
{
     m_model->saveData("data.csv");
}

void MainWindow::on_pushButton_3_clicked()
{
    m_model->saveData("index.html");
    ui->textBrowser->reload();
}

void MainWindow::on_stopReceiverButton_clicked()
{


    if ( ui->stopReceiverButton->text() == "stop receiver thread") {
         ui->stopReceiverButton->setText("start receiver thread");
         receiverThreadState = kIdleReceive ;
         timer->stop();
    }
    else {
         ui->stopReceiverButton->setText("stop receiver thread");
         receiverThreadState = kReceiveState;
         timer->start();
    }
}

void MainWindow::on_clearLogButton_clicked()
{
    m_model->removeRows(0,-1);
    m_model->saveData("index.html");
    ui->textBrowser->reload();
}

void MainWindow::on_reqAckBox_clicked()
{


}

void MainWindow::on_stopSendThreadButton_clicked()
{

dataThreadState = kIdleData;

}

void MainWindow::on_enableButtonsBox_clicked()
{
    if (!ui->enableButtonsBox->isChecked()) {
        ui->gbCheckCRC->setEnabled(false);
        ui->gbOpenImage->setEnabled(false);
        ui->gbWriteToFlash->setEnabled(false);
        ui->gbClearFlash->setEnabled(false);
        ui->gbClearFlash_2->setEnabled(false);
        ui->pbClearRAMBuffer->setEnabled(false);
    }
    else {
        ui->gbCheckCRC->setEnabled(true);
        ui->gbOpenImage->setEnabled(true);
        ui->gbWriteToFlash->setEnabled(true);
        ui->gbClearFlash->setEnabled(true);
        ui->gbClearFlash_2->setEnabled(true);
        ui->pbClearRAMBuffer->setEnabled(true);
    }
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_unknownComdButton_clicked()
{
    quint8          *canPackData = NULL;
    bool            ok;

    isDataTypeOfMsg              = false;

    int opcodeEdit, addrSenderEdit, addrReceiverEdit, isCmdBox, extCmdEdit, b7Box, b6Box, b5Box, b4Box;

    opcodeEdit          =  ui->opcodeEdit->text().toInt(&ok, 0);
    addrSenderEdit      =  ui->addrSenderEdit->text().toInt(&ok, 0);
    addrReceiverEdit    =  ui->addrReceiverEdit->text().toInt(&ok, 0);

    if (ui->isCmdBox->isChecked()) {
        isCmdBox = 0;
    }
    else {
        isCmdBox = 1;
    }

    extCmdEdit          =  ui->extCmdEdit->text().toInt(&ok, 0);


    if (ui->b7Box->isChecked()) {
        b7Box = 0;
    }
    else {
        b7Box = 1;
    }

    if (ui->b6Box->isChecked()) {
        b6Box = 0;
    }
    else {
        b6Box = 1;
    }

    if (ui->b5Box->isChecked()) {
        b5Box = 0;
    }
    else {
        b5Box = 1;
    }

    if (ui->b4Box->isChecked()) {
        b4Box = 0;
    }
    else {
        b4Box = 1;
    }

    createCanPacket( CanIdFill( isCmdBox, addrReceiverEdit, addrSenderEdit, b7Box, b6Box, b5Box,
                               b4Box, extCmdEdit, opcodeEdit), 0, canPackData, true );

    sizeSendPacketsQuery =  sendPacksQuery.size();

    cmdThreadState = kSendCommand;

    prACK = true;
}
