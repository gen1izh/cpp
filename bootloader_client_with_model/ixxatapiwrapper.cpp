#include "ixxatapiwrapper.h"
#include <math.h>
#include <QDebug>
#include "log.h"


/**
  *  Ixxat wrapper object
  */
IXXATApiWrapper            canInterface;

/**
  * ctor ECI
  */
IXXATApiWrapper::IXXATApiWrapper()
{
    hResult     = ECI_OK;

    stcHwPara.wHardwareClass = 0;
    stcHwPara.dwFlags   = 0;

    stcHwInfo.dwVer     = 0;
    dwHwIndex           = 0;
    dwCtrlIndex[0]      = 0;
    dwCtrlIndex[1]      = 0;
    dwCtrlHandle[0]     = ECI_INVALID_HANDLE;
    dwCtrlHandle[1]     = ECI_INVALID_HANDLE;
}

IXXATApiWrapper::~IXXATApiWrapper()
{
}

/**
  * Read CAN interface routine
  */
ECI_RESULT IXXATApiWrapper::_read( int canInterfaceNumber, ECI_CTRL_MESSAGE *msg, int *read_cnt ) {
    DWORD             dwCount         =   0;

    hResult       = ECI_ERR_TIMEOUT;
    dwCount = 1;

    msg->wCtrlClass                            = ECI_CTRL_CAN;
    msg->u.sCanMessage.dwVer                   = ECI_STRUCT_VERSION_V0;
    msg->u.sCanMessage.u.V0.uMsgInfo.Bits.ext  = 1;

    hResult = ECI10A_CtrlReceive( dwCtrlHandle[canInterfaceNumber], &dwCount, msg, ECIDEMO_RX_TIMEOUT);

    if( (ECI_OK == hResult) && (dwCount > 0) ) {
        EciPrintCtrlMessage(msg);
    }
    else {
        _errorToText();
    }
    *read_cnt = dwCount;
    return hResult;
}



/**
  * Write CAN interface routine
  */
ECI_RESULT IXXATApiWrapper::_write(int canInterfaceNumber, ECI_CTRL_MESSAGE msg, int msgType ) {
    if ( msgType == 0) cmdLog.add(" Enter to write routine...");
    hResult = ECI10A_CtrlSend( dwCtrlHandle[canInterfaceNumber], &msg, ECIDEMO_TX_TIMEOUT);
    if(ECI_OK != hResult) {
       if ( msgType == 0) cmdLog.add(" Error while sending CAN Messages ");
        qDebug() << "ECI10A_CtrlSend";
        _errorToText();
        hResult = ECI_OK;
        //break;
    }
    else {
        if ( msgType == 0) {
            cmdLog.add(" Cmd was sended successful...");
        }
    }
    return hResult;
}

/**
  * Initilize CAN interface routine
  */
void IXXATApiWrapper::_initialization() {
    cmdLog.add(" Initialize board. ");

    //memset( (ECI_HW_PARA *)&stcHwPara ,0 ,sizeof(stcHwPara));
    //memset( (ECI_HW_INFO *)&stcHwInfo ,0 ,sizeof(stcHwInfo));

    stcHwPara.wHardwareClass = ECI_HW_USB;

    hResult = ECI10A_Initialize(1, &stcHwPara);
    qDebug() << "ECI10A_Initialize";
    _errorToText();
    if( ECI_OK == hResult ) {
        hResult = ECI10A_GetInfo(dwHwIndex, &stcHwInfo);
        qDebug() << "ECI10A_GetInfo";
        _errorToText();
        if(ECI_OK == hResult) {
            EciPrintHwInfo(&stcHwInfo);
        }
    }
    if( ECI_OK == hResult ) {
        hResult = EciGetNthCtrlOfClass(&stcHwInfo,
                                       ECI_CTRL_CAN,
                                       0,
                                       &dwCtrlIndex[0]);
    }
    return;
}



/**
  * Open CAN interface routine
  */
void IXXATApiWrapper::_open( int canInterfaceNumber ) {
    cmdLog.add(QString(" Open interface 0x%1").arg( canInterfaceNumber ,0, 16));
    ECI_CTRL_CONFIG stcCtrlConfig;
    memset( &stcCtrlConfig, 0, sizeof(ECI_CTRL_CONFIG));
    stcCtrlConfig.wCtrlClass                = ECI_CTRL_CAN;
    stcCtrlConfig.u.sCanConfig.dwVer        = ECI_STRUCT_VERSION_V0;
    stcCtrlConfig.u.sCanConfig.u.V0.bBtReg0 = ECI_CAN_BT0_1000KB;
    stcCtrlConfig.u.sCanConfig.u.V0.bBtReg1 = ECI_CAN_BT1_1000KB;
    stcCtrlConfig.u.sCanConfig.u.V0.bOpMode = ECI_CAN_OPMODE_EXTENDED | ECI_CAN_OPMODE_ERRFRAME;
    hResult = ECI10A_CtrlOpen( &dwCtrlHandle[canInterfaceNumber], dwHwIndex, dwCtrlIndex[canInterfaceNumber], &stcCtrlConfig );
    qDebug() << "ECI10A_CtrlOpen";
    _errorToText();
    if( ECI_OK == hResult ) {
        ECI_CTRL_CAPABILITIES stcCtrlCaps ;
        memset( &stcCtrlCaps, 0, sizeof(ECI_CTRL_CAPABILITIES));
        hResult = ECI10A_CtrlGetCapabilities( dwCtrlHandle[canInterfaceNumber], &stcCtrlCaps );
        qDebug() << "ECI10A_CtrlGetCapabilities";
        _errorToText();
        if( ECI_OK == hResult ) {
            EciPrintCtrlCapabilities(&stcCtrlCaps);
        }
    }
    return;
}


/**
  * Start CAN interface routine
  */
void IXXATApiWrapper::_start(int canInterfaceNumber) {
    cmdLog.add(QString(" Start interface 0x%1").arg( canInterfaceNumber ,0, 16));
    if( ECI_OK == hResult ) {
        hResult = ECI10A_CtrlStart(dwCtrlHandle[canInterfaceNumber]);
        qDebug() << "ECI10A_CtrlStart";
        _errorToText();
    }
    return;
}


/**
  * Stop CAN interface routine
  */
void IXXATApiWrapper::_stop( int canInterfaceNumber ) {
    cmdLog.add(" << ENTER TO STOP ROUTINE >>");
    if( ECI_OK == hResult ) {
        hResult = ECI10A_CtrlStop(dwCtrlHandle[canInterfaceNumber], ECI_STOP_FLAG_NONE);
        qDebug() << "ECI10A_CtrlStop";
        _errorToText();
    }
    return;
}


/**
  * Close CAN interface routine
  */
void IXXATApiWrapper::_close(int canInterfaceNumber) {
    cmdLog.add(" << ENTER TO CLOSE ROUTINE >>");
    if( ECI_OK == hResult ) {
        hResult = ECI10A_CtrlStop(dwCtrlHandle[canInterfaceNumber], ECI_STOP_FLAG_RESET_CTRL);
        qDebug() << "ECI10A_CtrlStop";
        _errorToText();
    }
    hResult = ECI10A_CtrlClose(dwCtrlHandle[canInterfaceNumber]);
    dwCtrlHandle[canInterfaceNumber] = ECI_INVALID_HANDLE;
    return;
}

void IXXATApiWrapper::_errorToText()
{
    QString res = QString("0x%1").arg(hResult, 8, 16, QChar('0'));
    qDebug() << "Result code = " << res << " (" <<ECI10A_GetErrorString(hResult) << ")";
}


