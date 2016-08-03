
#include "ackextractor.h"

QMutex           mutex;

int             lastCommand;

AckExtractor::AckExtractor(){}
AckExtractor::~AckExtractor(){}


AckExtractor         dataExtractor;

/**
  * Extract state from answer
  */
void AckExtractor::_extractAck(ECI_CTRL_MESSAGE msg) {
    cmdLog.add(" Acknowledge by command ");
    cmdLog.add(" - CAN receive packet content: " );
    cmdLog.add(QString(" - ID  : 0x%1 ").arg(msg.u.sCanMessage.u.V0.dwMsgId,0,16) );
    cmdLog.add(QString(" - DLC : %1").arg(msg.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc) );
    QString data=" - DATA: ";
    for ( int i = 0; i < msg.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc; i++ ) {
        data+= QString("%1").arg(msg.u.sCanMessage.u.V0.abData[i],0,16) + " ";
    }
    cmdLog.add( data );
    cmdLog.refresh();
}



/**
 * Extract telemetry
 */
void AckExtractor::_extractTelemetry(ECI_CTRL_MESSAGE msg) {

    QTime time = QTime::currentTime();

    QString data = "";
    for ( int i = 0; i < msg.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc; i++ ) {
        data+= QString("0x%1").arg(msg.u.sCanMessage.u.V0.abData[i],0,16) + "("+QString(msg.u.sCanMessage.u.V0.abData[i])+")" +" ";
    }

    lastCommand     =  msg.u.sCanMessage.u.V0.abData[0];

    telemetryLog.add( QString(" time= %1; id = %2; data= %3 ").arg( time.toString("hh:mm:ss") ).arg( msg.u.sCanMessage.u.V0.dwMsgId,0, 16 ).arg(data) );
    telemetryLog.refresh();

    telemetryData = msg;


    qDebug()<<QString(" id = %2;  ").arg( msg.u.sCanMessage.u.V0.dwMsgId,0, 16 );

}



//
bool isStartPacket( hican_canid_t   hiCanId ) {
    if ( ( hiCanId.field.b7   == 0 ) &&
         ( hiCanId.field.b6   == 0 ) &&
         (( hiCanId.field.code == PROTO_OP_WRITE ) ||
          ( hiCanId.field.code == PROTO_OP_ERASE_AND_WRITE )) )
        return true;
    else
        return false;
}

//
bool isNeedShow( sendMsgArray msg ) {
    if ( msg.show == true )
        return true;
    else
        return false;
}

//
bool isData(){
    if ( isDataTypeOfMsg == true )
        return true;
    else
        return false;
}

//
bool isTelemetry( hican_canid_t   hiCanId ) {
    if (( isDataTypeOfMsg  == true ) &&  ( hiCanId.field.code == PROTO_OP_TELEMETRY ))
        return true;
    else
        return false;
}



/**
  * Функция подготавливает данные для добавления их в модель
  */
void AckExtractor::oneRecordFill(sendMsgArray msg ) {

    mutex.lock();
    hican_canid_t   hiCanId;
    hiCanId.value               =   msg.msg.u.sCanMessage.u.V0.dwMsgId;
    QTime           time        =   QTime::currentTime();
    QStringList     record;
    bool            pr          =   false;

/**
  * 1) если стартовый пакет команды врайт или врайт_и_ирейз и при этом тип пакета - данные
  * 2) если тип пакета - команда
  * 3) если стоповый пакет и команда (врайт)
  * 4) если прет телеметрия
  * 5) если идет длительная операция и выдали команду***
  */
    if ( isNeedShow(msg) )
//        if ( ( isStartPacket( hiCanId ) && isData() ) /*|| (( hiCanId.field.b7   == 1 ) && (hiCanId.field.kind == 0))*/ || isTelemetry( hiCanId ) )
    {

        record.append(QString(" %1 ").arg( time.toString("hh:mm:ss") ));

        if (hiCanId.field.code == PROTO_OP_TELEMETRY) {
            record.append("telemetry");
            record.append("0xff");

            if ( ( hiCanId.field.b7 == 1 ) && ( hiCanId.field.b6 == 1 ) ) {
                //stop
                for ( int i = 0; i < msg.msg.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc; i++ ) {
                    telemtryBuf.buf[telemtryBuf.indx]= msg.msg.u.sCanMessage.u.V0.abData[i];
                    telemtryBuf.indx++;
                }
                pr = true;
            }

            if ( ( hiCanId.field.b7 == 0 ) && ( hiCanId.field.b6 == 1 ) ) {
                //data
                for ( int i = 0; i < msg.msg.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc; i++ ) {
                    telemtryBuf.buf[telemtryBuf.indx]= msg.msg.u.sCanMessage.u.V0.abData[i];
                    telemtryBuf.indx++;
                }
            }

            if ( ( hiCanId.field.b7 == 0 ) && ( hiCanId.field.b6 == 0 ) ) {
                //start
                telemtryBuf.indx=0;
                for ( int i = 0; i < msg.msg.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc; i++ ) {
                    telemtryBuf.buf[telemtryBuf.indx]= msg.msg.u.sCanMessage.u.V0.abData[i];
                    telemtryBuf.indx++;
                }
            }
        }
        else if (hiCanId.field.code == PROTO_OP_ENTER_BOOTLOADER) {
            if (hiCanId.field.b7 == 1)
                record.append("ack");
            else if (hiCanId.field.b7 == 0 )
                record.append("cmd");
            record.append("enter to bootloader");
        }
        else if (hiCanId.field.code == PROTO_OP_WRITE)  {
            if ((hiCanId.field.b7 == 1)) {
                record.append("ack");
            }
            else if ( hiCanId.field.b7 == 0 )
                record.append("cmd");

            record.append("writer");
        }
        else if (hiCanId.field.code == PROTO_OP_ERASE_AND_WRITE)  {
            if (hiCanId.field.b7 == 1)
                record.append("ack");
            else if (hiCanId.field.b7 == 0 )
                record.append("cmd");
            record.append("erase and writer");
        }
        else if (hiCanId.field.code == PROTO_OP_SET_ACTIVE_IMAGE)  {
            if (hiCanId.field.b7 == 1)
                record.append("ack");
            else if (hiCanId.field.b7 == 0 )
                record.append("cmd");
            record.append("set active image");
        }
        else if (hiCanId.field.code == PROTO_OP_LOAD_IMAGE)  {
            if (hiCanId.field.b7 == 1)
                record.append("ack");
            else if (hiCanId.field.b7 == 0 )
                record.append("cmd");
            record.append("load image");
        }
        else if (hiCanId.field.code == PROTO_OP_VERIFY_IMAGE)  {
            if (hiCanId.field.b7 == 1)
                record.append("ack");
            else if (hiCanId.field.b7 == 0 )
                record.append("cmd");
            record.append("verify image");
        }
        else if (hiCanId.field.code == PROTO_OP_ERASE_AREA)  {
            if (hiCanId.field.b7 == 1)
                record.append("ack");
            else if (hiCanId.field.b7 == 0 )
                record.append("cmd");
            record.append("erase area");
        }
        else {
            if (hiCanId.field.b7 == 1)
                record.append("ack");
            else if (hiCanId.field.b7 == 0 )
                record.append("cmd");
            record.append("unknown command");
        }

        record.append(QString("%1").arg(hiCanId.field.raddr,0,16)) ;
        record.append(QString("%1").arg(hiCanId.field.saddr,0,16)) ;

        quint8 value = (hiCanId.field.b7<<3) | (hiCanId.field.b6<<2) | (hiCanId.field.b5<<1) | (hiCanId.field.b4);
        record.append( QString("0x%1").arg( value, 0, 16 ));
        QString st;
        st = "";
        if (!pr) {
            for ( int i = 0; i < msg.msg.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc; i++ ) {
                st+= QString("%1").arg(msg.msg.u.sCanMessage.u.V0.abData[i],0,16) + " ";
            }
        }
        else {
            for ( int i = 0; i < telemtryBuf.indx; i++ ) {
                st+= QString("%1").arg(telemtryBuf.buf[i],0,16) + " ";
            }

        }
        record.append(st);
        oneRecord.append(record);
    }

    mutex.unlock();
}

/**
  *  Route answer to extract data
  */
void AckExtractor::_routePacket( sendMsgArray msg ) {

    hican_canid_t hiCanId;

    hiCanId.value = msg.msg.u.sCanMessage.u.V0.dwMsgId;

    oneRecordFill(msg);



    switch ( hiCanId.field.code ) {
    case PROTO_OP_TELEMETRY: // telemetry
        _extractTelemetry( msg.msg );
        break;
    case PROTO_OP_ENTER_BOOTLOADER: // enter to bootloader
        _extractAck( msg.msg );
        break;

    case PROTO_OP_WRITE: //
        _extractAck( msg.msg );
        break;
    case PROTO_OP_ERASE_AND_WRITE: //
        _extractAck( msg.msg );
        break;
    case PROTO_OP_SET_ACTIVE_IMAGE: //
        _extractAck( msg.msg );
        break;
    case PROTO_OP_LOAD_IMAGE: //
        _extractAck( msg.msg );
        break;
    case PROTO_OP_VERIFY_IMAGE: //
        _extractAck( msg.msg );
        break;
    case PROTO_OP_ERASE_AREA: //
        _extractAck( msg.msg );
        break;
    default:
        qDebug()<<"come to default";
        _extractAck( msg.msg );
        break;
    };

}
