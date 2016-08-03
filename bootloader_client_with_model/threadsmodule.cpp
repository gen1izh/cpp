#include "threadsmodule.h"

volatile CmdThreadState     cmdThreadState;
volatile DataThreadState    dataThreadState;
volatile ReceiverThreadState receiverThreadState;

senderThread                sendCanMsgThread;
receiverThread              receiveCanMsgThread;
createSenderThread          createSenderCanMsgThread;

bool                        isDataTypeOfMsg;


senderThread::senderThread() {
}

senderThread::~senderThread() {
}

bool prACK;

/**
  * Send command and data thread
  */
void senderThread::run() {

    cmdThreadState  = kIdleCmd;
    isDataTypeOfMsg = false;
    sendMsgArray     packFromArray;

    msleep(2000);
    forever {
        switch( cmdThreadState ) {
        case kSendCommand:
            msleep(1);
           if ( !sendPacksQuery.isEmpty() ) {
               packFromArray = (sendMsgArray) sendPacksQuery.takeFirst();
           }
            dataExtractor.oneRecordFill( (sendMsgArray)packFromArray );
            InteractInterface->performSend( CAN_INTERFACE1, &packFromArray.msg, isDataTypeOfMsg );
            if ( sendPacksQuery.isEmpty() ) {
                qDebug()<<"md sended";
                cmdThreadState = kIdleCmd;
                sPacketsBar.refresh();
                waitCond.wakeAll();
            }
            else {
                sPacketsBar.refresh();
            }
            if ( !isDataTypeOfMsg ) cmdLog.refresh();
            break;
        case kIdleCmd:
            msleep(20);
            break;
        }
    }
}



receiverThread::receiverThread() {
}

receiverThread::~receiverThread() {
}



/**
  * Send\receive command thread
  */
void receiverThread::run() {
    sendMsgArray        packFromArray;
    ECI_CTRL_MESSAGE    msg;

    cmdLog.add("  ");

    cmdLog.refresh();
    msleep(2000);
    forever {
        msleep(200);

        switch (receiverThreadState) {
        case kReceiveState:

            if ( InteractInterface->performReceive( CAN_INTERFACE0, &msg ) == 0 ) {
                packFromArray.msg   = msg;
                packFromArray.show  = true;
                qDebug() << "can1";
                dataExtractor._routePacket( packFromArray );
            }

            if ( InteractInterface->performReceive( CAN_INTERFACE1, &msg ) == 0 ) {
                packFromArray.msg   = msg;
                packFromArray.show  = true;
                 qDebug() << "can2";
                dataExtractor._routePacket( packFromArray );
            }

            break;
        case kIdleReceive:
            InteractInterface->performReceive( CAN_INTERFACE0, &msg );
            InteractInterface->performReceive( CAN_INTERFACE1, &msg );
            msleep(20);
            break;
        default:
            break;
        }
    }
}




/**
  * ======================================================================================================
  */

createSenderThread::createSenderThread() {
}

createSenderThread::~createSenderThread() {
}


void createSenderThread::run() {

    quint16          start_addr;
    quint8           start_pack[8];
    quint8           countMd=0;
    quint8          *tmpBuf;
    quint32          size;
    QMutex           mutex;
    int              ival;
    int              dval;

    msleep(2000);

    forever {

        switch( dataThreadState ) {
        case kSendDataArray:
            //start_addr = prt_atm_extract_word( canPackData, 0 );

           start_addr = (quint16) ( (quint16) canPackData[0]) | ( (quint16) canPackData[1] << 8 );

            prt_atm_construct_word( start_pack, 0, (start_addr + countMd) );
            start_pack[2] = 0;
            start_pack[3] = doperations._currentPosX;
            prt_atm_construct_dataword(start_pack, 4, doperations._mdCrc32[countMd]);
   /**
    * Send start packet
    */
            createCanPacket( CanIdFill(1,RECEIVER_ADDR,SENDER_ADDR,0,0,0,0,0,writeOrEraseWriteOperation), 8, (quint8 *)&start_pack[0],false );
            // cmdThreadState = kSendCommand;

   /**
    *Sendind data
    */

            if ( doperations._currentPosX > countMd  )  size = MD_SIZE;
            if ( doperations._currentPosX == countMd  ) size = doperations._currentPosY;

            tmpBuf = ( quint8 *)&(doperations._md[countMd][0]);

            ival = size / 8;
            dval = size % 8;

            int i;

            for ( i = 0; i < ival; i++ ) {
                if ((dval == 0) && (ival == i + 1)) {
                    /**
                     *Stop packet
                     */
                    createCanPacket(  CanIdFill(1,RECEIVER_ADDR,SENDER_ADDR,1,1,0,0, i&0xF,writeOrEraseWriteOperation) , 8 , tmpBuf, false );
                }
                else {


                    createCanPacket(  CanIdFill(1,RECEIVER_ADDR,SENDER_ADDR,0,1,0,0, i&0xF,writeOrEraseWriteOperation) , 8 , tmpBuf, false );
                }
                tmpBuf+=8;
            }

            if ( dval > 0 ) {
     /**
      *Stop packet
      */
                createCanPacket(  CanIdFill(1,RECEIVER_ADDR,SENDER_ADDR,1,1,0,0, i&0xF,writeOrEraseWriteOperation) , dval , tmpBuf, false );
            }

            countMd++;
            sizeSendPacketsQuery    =  sendPacksQuery.size();
            cmdThreadState          = kSendCommand;
            isDataTypeOfMsg         = true;


            dataThreadState = kWaitCompleteOperation;

            mutex.lock();
            waitCond.wait( &mutex );
            mutex.unlock();

            // dataThreadState = kIdleData;
            break;
        case kWaitCompleteOperation:
            msleep(2);

            if ((( (lastState == statesCodes.key("BOOTLOADER_SUCCESSFUL")) || (lastState & 0x80) ) && ( countMd == 0 ))
                    || ((countMd!=0) && (lastState == statesCodes.key("BOOTLOADER_SUCCESSFUL")) && ((lastCommand == PROTO_OP_ERASE_AND_WRITE)||( lastCommand == PROTO_OP_WRITE)) ))  {
                if ( doperations._currentPosX >= countMd ) {
                    dataThreadState = kSendDataArray;
                }
                else {
                    dataThreadState = kIdleData;
                    cmdLog.add(" Image successful was writed!!! ");
                }
            }
            else {
                asm( "nop;nop;nop;nop;nop;nop;" );
            }
            break;
        case kIdleData:
            msleep(2);
            countMd = 0;
            break;
        default:
            break;
        }

    }

}


