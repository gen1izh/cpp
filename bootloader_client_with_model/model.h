#ifndef MODEL_H
#define MODEL_H
#include <QtGui/QApplication>
#include <QtGui>


class model : public QAbstractTableModel {

    Q_OBJECT

    QList<QStringList> *m_records;

public:
    model(QObject *parent=0);
    ~model();

    int rowCount(const QModelIndex& parent=QModelIndex()) const;

    int columnCount(const QModelIndex& parent=QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const;

    bool hasChildren(const QModelIndex& parent=QModelIndex() ) const;

    bool setData(const QModelIndex &index, const QVariant& value, int role=Qt::EditRole);



    bool insertRows(int row, int count, QStringList rec, const QModelIndex &parent=QModelIndex() );

    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

    bool loadData(const QString &fileName);

    bool saveData(const QString &fileName);

};


typedef struct {
    quint16  addr;
    quint8   indx;
    quint8   size;
    quint32  crc;
}_mapWriteDataArrayStruct;


typedef struct {
    quint16  addr;
    quint8   size;
}_mapEraseAreaStruct;


//typedef struct {
//    quint8   zero00;
//    quint8   zero01;
//    quint8   zero02;
//    quint8   isNegative;
//    quint8   zero03;
//    quint8   zero04;
//    quint8   ackType;
//    quint8   chanNum;
//}_mapAckStruct;


typedef struct {
    quint8   correctFlags;
    quint8   ceraseFlags;
}_mapTelemetryFlagsStruct;


typedef struct {
    quint8   code;
    quint8   telemetry_code;
    quint16  len;
    quint8   abon_code;
    quint8   tm_exp;
    quint16  telemetry_counter;
    quint8   lastCmd;
    quint8   lastState;
    quint16  addr;
    quint8   bootloaderState;
    quint8   mdKol;
    _mapTelemetryFlagsStruct flags[32];
}_mapTelemetryStruct;

typedef struct {
    quint8   buf[244];
    quint8   indx;
}_mapTelemetryBufStruct;

/*
 *  5th byte from the data[8] of Acknowledge message.
 */
typedef union hican_ack_report_u {

  /*
   *  Whole value of the Acknowledge Report.
   */
  quint8 value;

  /*
   *  Fields of the Acknowledge Report.
   */
struct hican_ack_report_fields_s {
  unsigned  channel:      1;  /* CAN_0(0), CAN_1(1) */
  unsigned  kind:         1;  /* CMD_PKT_KIND(0), ARRAY_PKT_KIND(1) */
  unsigned  reserv54:     2;
  unsigned  err_invalid:  1;  /* CODE_EXIST(0) - ok, CODE_INVALID(1) - error for Command
                                 TYPE_EXIST(0) - ok, TYPE_INVALID(1) - error for Array */
  /*
   *  Only for Array:
   */
  unsigned  err_start:    1;  /* START_RECEIVED(0) - ok, START_LOST(1) - error  */
  unsigned  err_gap:      1;  /* FULL_ARRAY(0) - ok, GAP_IN_ARRAY(1) - error */
  unsigned  err_checksum: 1;  /* CHECKSUM_OK(0) - ok, CHECKSUM(1) - error */
} field;

} _mapAckStruct;

extern _mapTelemetryBufStruct telemtryBuf;


#endif // DBOPERATIONS_H
