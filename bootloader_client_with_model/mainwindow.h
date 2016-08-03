#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui/QApplication>
#include <QMainWindow>
#include <QWaitCondition>
#include "ixxatapiwrapper.h"
#include "log.h"
#include "model.h"
#include "ixxatapiwrapper.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include "crc.h"
#include "threadsmodule.h"
#include <QWaitCondition>
#include "ackextractor.h"
#include "dataoperations.h"
#include <QSortFilterProxyModel>
#include <QTimer>
#include <QStandardItemModel>

#include "interfaceStrategy.h"
#include "gresbStrategyRelease.h"

extern ECI_CTRL_MESSAGE    telemetryData;


/* -------------------------------------------------------------------------- */
/*                                  Command                                   */
/* -------------------------------------------------------------------------- */
/*
 *  For CMD canid.field.ctl.command.attr.req.is_ack always HICAN_CMD_PKT !
 */
#define HICAN_CMD_PKT                 0
/*
 *  For ACK canid.field.ctl.command.attr.ack.is_ack always HICAN_ACK_PKT !
 */
#define HICAN_ACK_PKT                 1
/*
 *  Values of canid.field.ctl.command.attr.req.need_ack
 */
#define HICAN_CMD_PKT_WITH_ACK        1
#define HICAN_CMD_PKT_WITHOUT_ACK     0
/*
 *  Values of canid.field.ctl.command.attr.req.with_params
 */
#define HICAN_CMD_PKT_WITH_PARAMS     1
#define HICAN_CMD_PKT_WITHOUT_PARAMS  0


/**
 *   CAN Message Identifier of the HiCAN Packet.
 */
typedef union hican_canid_u {

  /*
   *  Whole value of the CAN Identifier for HiCAN packet.
   */
   quint32    value;

  /*
   *  Structured HiCAN packet with fields accessed separately.
   */
   struct hican_canid_fields_s {

    /*
     *  29..16 bits of the address(reference) field: KIND, SADDR, RADDR subfields
     */

      unsigned  code:    8;
      unsigned  extend:  4;
      unsigned  b4:      1;
      unsigned  b5:      1;
      unsigned  b6:      1;
      unsigned  b7:      1;
      unsigned  raddr:   6;  /* Value in [0..63] */
      unsigned  saddr:   6;  /* Value in [0..63] */
      unsigned  kind:    1;  /* CMD_PKT_KIND(0), ARRAY_PKT_KIND(1), ACK_PKT_KIND(0) */
      unsigned  unused:  3;  /* Never used, aligns to 32 bit */

  } field;

} hican_canid_t;


#define prt_atm_construct_dataword(packet_data, i, word) \
  packet_data[i]   = (quint8) ( 0xff & ( word ) ); \
  packet_data[i+1] = (quint8) ( 0xff & ( word >> 8) ); \
  packet_data[i+2] = (quint8) ( 0xff & ( word >> 16) ); \
  packet_data[i+3] = (quint8) ( 0xff & ( word >> 24)  );

#define prt_atm_construct_word(packet_data, i, word) \
  packet_data[i] =   (quint8) ( 0xff & (word ) ); \
  packet_data[i+1] = (quint8) ( 0xff & (word >> 8)  );


#define prt_atm_extract_dataword(packet_data, i) \
       ( (quint32) packet_data[i]   << 24 ) \
     | ( (quint32) packet_data[i+1] << 16 ) \
     | ( (quint32) packet_data[i+2] << 8  ) \
     |   (quint32) packet_data[i+3];


#define prt_atm_extract_word(packet_data, i) \
       ( (quint16) packet_data[i]) \
     | ( (quint16) packet_data[i+1] << 8 )

extern QWaitCondition waitCond;
extern int            lastState;
extern quint8         canPackData[8];
extern int            sizeSendPacketsQuery;
extern int            writeOrEraseWriteOperation;
extern QHash<int, QString> statesCodes;
extern QHash<int, QString> operationCodes;
extern QHash<int, QString> abonCodes;

namespace Ui {
class MainWindow;
}

class view;
class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    void setViewForm();


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void createCanPacket(int id, int len, quint8 *buf);

public slots:
    void addEventToView();

private slots:
    /**
      * Open image file, calculate crc32 and send image by can line
      */
    void on_pbOpenImageFile_clicked();
    /**
      * Refresh log
      */
    void refresh_log();
    /**
      * Refresh telemetry
      */
    void refresh_telemetry();

    /**
      * Refresh statusBar
      */
    void refresh_sendPacketsBar();

    /**
      * Clear RAM buffer command
      */
    void on_pbClearRAMBuffer_clicked();

    /**
      * Clear Flash
      */
    void on_pbClearFlash_clicked();
    /**
      * Write to flash
      */
    void on_pbWriteToFlash_clicked();

    /**
      * Enter bootloader
      */
    void on_pbEnterBootloader_clicked();

    /**
      * Verify data
      */
    void on_VerifyButton_clicked();

    void on_setActiveButton_clicked();

    void on_pushButton_clicked();

    void on_loadCsvButton_clicked();

    void on_saveCsvButton_clicked();

    void on_pushButton_3_clicked();

    void on_stopReceiverButton_clicked();

    void on_clearLogButton_clicked();

    void on_reqAckBox_clicked();

    void on_stopSendThreadButton_clicked();

    void on_enableButtonsBox_clicked();

    void on_pushButton_2_clicked();

    void on_unknownComdButton_clicked();

private:
    Ui::MainWindow *ui;

    model                   *m_model;
    QSortFilterProxyModel   *proxyModel;
};


/**
  * Fill Can Id
  */
unsigned int CanIdFill( int msgType, int AO,
                        int AP,      int b7,
                        int b6,      int b5,
                        int b4,      int ExtCmd,
                        int opcode);

/**
  * Create can packet to send
  */
void createCanPacket(int id, int len, quint8 *buf, bool show);


#define    BOOTLOADER_ERROR    0x80

/**
  * Can identificator data
  */
typedef union {
    unsigned int  value;
    struct {
        unsigned opcode:                8;
        unsigned extCmd:                4;
        unsigned b4:                    1;
        unsigned b5:                    1;
        unsigned b6:                    1;
        unsigned b7:                    1;
        unsigned AP:                    6;
        unsigned AO:                    6;
        unsigned msgType:               1;
        unsigned reserved:              3;

    } flags;
}CanIdStruct;



#endif // MAINWINDOW_H
