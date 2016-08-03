#include "model.h"
#include "mainwindow.h"


_mapTelemetryBufStruct telemtryBuf;


/**
  * Разбирает csv фаил на строки
  */
QStringList splitCSVLine(const QString& line) {
    bool            inItem = false;
    QStringList     items;
    QString         item;

    for(int pos = 0; pos < line.length(); pos++) {
        QChar c= line.at(pos);
        if( c == '\"'){
            if (inItem) {
                items.append(item);
                item = "";
            }
            inItem = !inItem;
        }else
            if (inItem)
                item +=c;
    }
    return items;
}

/**
  * конструктор. создает объект записей
  */
model::model(QObject *parent)
{
    m_records = new QList<QStringList>;      
}

/**
  * деструктор. удаляет объект записей
  */
model::~model()
{
    m_records->clear();
    delete m_records;
}

/**
  * Возвращает количество записей в моделе
  */
int model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || m_records->count() == 0)
        return 0;
    else
        return m_records->count()-1;
}

/**
  * Возвращает количество колонок в записи моделе
  */
int model::columnCount(const QModelIndex &parent) const
{
    if (m_records->count())
        return m_records->at(0).count();
    else
        return 0;
}

/**
  *
  */
QVariant model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (!m_records->count())
        return QVariant();
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole)
            return m_records->at(0).at(section);
    }
    else if (orientation == Qt::Vertical) {
        if (role == Qt::DisplayRole)
            return section+1;
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

/**
  *
  */
Qt::ItemFlags model::flags(const QModelIndex &index) const
{
    if (!index.isValid() || !m_records->count())
        return 0;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

/**
  *
  */
QVariant model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_records->count())
        return QVariant();

    if ( role == Qt::SizeHintRole )
        return QSize(30,12);

    QStringList record = m_records->at(index.row()+1);
    if ( role == Qt::DisplayRole || role == Qt::EditRole)
        return record.at(index.column());

    if (role == Qt::ToolTipRole) {
        QString tip, key, value;
        tip = "<table>";
        int maxLines = record.count();

        for ( int i = 0; i< maxLines; i++) {
            key =headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
            value = record.at(i);
            if (!value.isEmpty())
                tip += QString("<tr><td><b>%1</b>: %2 </td></tr>").arg(key,value);
        }
        tip+="</table>";
        return tip;
    }
    return QVariant();
}

/**
  *
  */
bool model::hasChildren(const QModelIndex &parent) const
{
    return !parent.isValid();
}

/**
  * хз пока не использовал, но для модели нужна видимо
  */
bool model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid()&&(role == Qt::EditRole || role == Qt::DisplayRole)) {
        (*m_records)[index.row()+1][index.column()] = value.toString();
        emit dataChanged(index,index);
        return true;
    }
    return false;
}


/**
  * Функция вставки записи по номеру row строки. Если row = 1, то в 1 строку будет вставлять всегда.
  */
bool model::insertRows(int row, int count, QStringList rec, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (row == -1) {
        row = 0;
    }

    beginInsertRows(QModelIndex(),row,row+count-1);

    for ( int i = 0; i < count; i++ )
        m_records->insert(row+1,rec);

    endInsertRows();
    return true;
}


/**
  * Удалить ячейки
  */
bool model::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (row+count>m_records->count()-1)
        return false;
    if ( count == -1 ) {
        count = m_records->size() ;
    }
        beginRemoveRows(QModelIndex(), row, row+count-1);
        for (int i=0; i<count; i++)
            m_records->removeAt(row+1);
        endRemoveRows();

    return true;
}

/**
  * Загрузить данные. Данные хранятся в CSV фаиле.
  */
bool model::loadData(const QString &fileName)
{
    QFile file(fileName);
    int fdstate = file.open(QIODevice::ReadOnly|QIODevice::Text);
    if (!fdstate)
        return false;

    m_records->clear();
    QTextStream in(&file);
    in.setCodec("CP1251");
    while(!in.atEnd()) {
        QString line=in.readLine();
        m_records->append(splitCSVLine(line));
    }
    file.close();
    reset();
    return ( in.status() == QTextStream::Ok );
}



/**
  * Макрос для квитанций
  */
#define   ackret() \
ackStruct =  (_mapAckStruct *)&data8[5]; \
QString ackType, chanNum, isNegative; \
if (ackStruct->field.kind) { \
    ackType = "ack on array"; \
} \
else { \
    ackType = "ack on cmd"; \
} \
if (ackStruct->field.channel == 0) { \
    chanNum = "by CAN 1"; \
} \
else { \
    chanNum = "by CAN 2"; \
} \
if (ackStruct->field.err_invalid == 1) { \
    isNegative = "negative ack"; \
} \
else { \
    isNegative = "successful ack"; \
} \
return "type packet: <strong>ACK</strong> ; <br> params:<br>" \
        "type of ack: <strong>"+ackType+"</strong><br>" \
        "channel number: <strong>"+chanNum+"</strong><br>"  \
        "is negative: <strong>"+isNegative+"</strong><br>"





/**
  * Функция подробного разбора данных ответа(телеметрии или квитанции)
  */
QString FullDescriptionParams(QString pktType, QString codeName, QString attr, QString data){

    _mapWriteDataArrayStruct    *writeMap;
    _mapEraseAreaStruct         *eraseArea;
    _mapAckStruct               *ackStruct;
    _mapTelemetryStruct         *Telemetry;
    bool                        ok;

    QStringList st = data.split(" ", QString::SkipEmptyParts);
    quint8      data8[255];

    for (int i = 0; i < st.size(); i++ ) {
        data8[i] = (quint8)st.at(i).toUInt(&ok,16);
    }

    if (pktType == "telemetry") {

        if ( attr.toInt(&ok,0) == 0x4 ) {
//data

            return "<table><tr><td>   <strong><i>type packet</i></strong>:    </td><td>                         telemetry                        </td></tr>"
                    "<tr><td>  <strong><i>params</i></strong>      </td><td>                                                                      </td></tr>"
                    "<tr><td>  <strong><i>data</i></strong>      </td><td>                             "+data+"                                   </td></tr></table>";
        }
        if ( attr.toInt(&ok,0) == 0xC) {
//stop

            Telemetry  = (_mapTelemetryStruct *)&data8[0];
            return "<table align =\"left\"><tr><td>   <strong><i>type packet</i></strong>:    </td><td>                         telemetry                        </td></tr>"
                    "<tr><td>  <strong><i>params</i></strong>      </td><td>                                                                        </td></tr>"
                    "<tr><td>  code:               </td><td>      <strong>"+QString("0x%1").arg( Telemetry->code,0,16)+"</strong>                   </td></tr>"
                    "<tr><td>  abon_code :         </td><td>      <strong>"+ abonCodes[Telemetry->abon_code]+"</strong>                             </td></tr>"
                    "<tr><td>  tm_exp:             </td><td>      <strong>"+QString("%1").arg( Telemetry->tm_exp,0,10)+"</strong>                   </td></tr>"
                    "<tr><td>  telemetry_code:     </td><td>      <strong>"+QString("0x%1").arg( Telemetry->telemetry_code,0,16)+"</strong>         </td></tr>"
                    "<tr><td>  telemetry_counter:  </td><td>      <strong>"+QString("%1").arg( Telemetry->telemetry_counter,0,10)+"</strong>        </td></tr>"
                    "<tr><td>  last command:        </td><td>      <strong>"+ operationCodes[Telemetry->lastCmd]+"</strong>                         </td></tr>"
                    "<tr><td>  last state:          </td><td>      <strong>"+ statesCodes[Telemetry->lastState]             +"</strong>             </td></tr>"
                    "<tr><td>  length telemetry:    </td><td>      <strong>"+QString("%1").arg( Telemetry->len,0,10)+"</strong>                     </td></tr>"
                    "<tr><td>  bootloader state:    </td><td>      <strong>"+QString("0x%1").arg( Telemetry->bootloaderState,0,16)+"</strong>       </td></tr>"
                    "<tr><td>  data arrays count:   </td><td>      <strong>"+QString("%1").arg( Telemetry->mdKol,0,10)+"</strong>                   </td></tr></table>";

        }
        if ( attr.toInt(&ok,0) == 0x0 ) {
//start

        return "<table><tr><td>   <strong><i>type packet</i></strong>:    </td><td>                         telemetry                        </td></tr>"
                "<tr><td>  <strong><i>params</i></strong>      </td><td>                                                                      </td></tr>"
                "<tr><td>  <strong><i>data</i></strong>      </td><td>                             "+data+"                                   </td></tr></table>";

        }
    }
    else {

        if ( codeName == "enter to bootloader") {
            if ( attr.toInt(&ok,0) & 0x08) {
            // ack
                ackret();
            }
            else {
            //cmd
                return "<strong><i>type packet</i></strong>: cmd  <br> <strong><i>params</i></strong>: without params<br>";
            }
        }
        if ( codeName == "writer") {
            if ( attr.toInt(&ok,0) & 0x08) {
            // ack
                ackret();
            }
            else {
            //cmd
                writeMap = (_mapWriteDataArrayStruct *)&data8[0];

                return "<strong><i>type packet</i></strong>: cmd  <br> <strong><i>params</i></strong>:<br>"
                        "addr: <strong>"+QString("0x%1").arg(writeMap->addr,0,16)+"</strong><br>"
                        "index md: <strong>"+QString("%1").arg(writeMap->indx,0,10)+"</strong><br>"
                        "kol md: <strong>"+QString("%1").arg(writeMap->size,0,10)+"</strong><br>"
                         "crc: <strong>"+QString("0x%1").arg( writeMap->crc,0,16)+"</strong><br>";
            }
        }
        if ( codeName == "erase and writer") {
            if ( attr.toInt(&ok,0) & 0x08) {
            // ack
                ackret();
            }
            else {
            //cmd
                writeMap = (_mapWriteDataArrayStruct *)&data8[0];

                return "<strong><i>type packet</i><strong>: cmd  <br> <strong><i>params</i></strong>:<br>"
                        "addr: <strong>"+QString("0x%1").arg(writeMap->addr,0,16)+"</strong><br>"
                        "index md: <strong>"+QString("%1").arg(writeMap->indx,0,10)+"</strong><br>"
                        "kol md: <strong>"+QString("%1").arg(writeMap->size,0,10)+"</strong><br>"
                         "crc: <strong>"+QString("0x%1").arg( writeMap->crc,0,16)+"</strong><br>";
            }
        }

        if ( codeName == "set active image") {
            if ( attr.toInt(&ok,0) & 0x08) {
            // ack
                ackret();
            }
            else {
            //cmd
                quint16 *addr;
                addr= (quint16 *)&data8[0];
                return "<strong><i>type packet</i></strong>: cmd  <br> <strong><i>params</i></strong>:<br>"
                        "addr: <strong>"+QString("0x%1").arg(*addr,0,16)+"</strong><br>";
            }
        }
        if ( codeName == "load image") {
            if ( attr.toInt(&ok,0) & 0x08) {
            // ack
                ackret();
            }
            else {
            //cmd
             return "<strong><i>type packet</i><strong>: cmd  <br> <strong><i>params</i></strong>:<br>";
            }
        }
        if ( codeName == "verify image") {
            if ( attr.toInt(&ok,0) & 0x08) {
            // ack
                ackret();
            }
            else  {
            //cmd
                quint16 *addr;
                addr= (quint16 *)&data8[0];
                return "<strong><i>type packet</i><strong>: cmd  <br> <strong><i>params</i></strong>:<br>"
                        "addr: <strong>"+QString("0x%1").arg(*addr,0,16)+"</strong><br>";
            }
        }
        if ( codeName == "erase area") {
            if ( attr.toInt(&ok,0) & 0x08) {
            // ack
                ackret();
            }
            else {
            //cmd
                eraseArea= (_mapEraseAreaStruct *)&data8[0];                             
                return "<strong><i>type packet</i><strong>: cmd  <br> <strong><i>params</i></strong>:<br>"
                        "addr: <strong>"+QString("0x%1").arg(eraseArea->addr,0,16)+"</strong><br>"
                        "size: <strong>"+QString("%1").arg(eraseArea->size,0,10)+"</strong><br>";
            }
        }
    }

    return "opa";
}



/**
  * Сохранение данных. Сохранение происходит
  * либо в csv фаил либо в html.
  */
bool model::saveData(const QString &fileName)
{
    bool ok;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
        return false;

    QTextStream out(&file);

    if ( QFileInfo(fileName).suffix() == "csv" ) {
        foreach(QStringList record, *m_records) {
            QString s="\"";
            s+=record.join("\",\"");
            s+="\"\n";
            out<<s;
        }
    }
    else {

        out << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">"
               "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"ru\">"
               "<head>"
               "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">"
               "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=EmulateIE7\">"
               "<title>LOG</title>"
               "<link rel=\"stylesheet\" type=\"text/css\" href=\"main.css\">"
               "</head>"
               "<body>";

        out<<"<font size=\"4\" face=\"arial\">  <center> <table>";
        int i=0; // for header not parse
        foreach(QStringList record, *m_records) {
            QString background;

            if (record.size() < 6 ) {
                int i = 0;
                i=90;
            }

            if (i>0) {
                if ( record[1] == "telemetry" ) {
                    background = "brd_body_telemetry";
                }
                else if (record[1] == "ack" ) {
                    background = "brd_body_ack";
                }
                else
                    background = "brd_body_cmd";


                QString AttrDesc, needAck, b6param;
                if (record[1] =="telemetry") {
                    if (  (record.at(5).toInt(&ok,16)) == 0x4) {
                        AttrDesc ="data packet";
                    }
                    if (  (record.at(5).toInt(&ok,16)) == 0xC) {
                        AttrDesc ="stop packet";
                    }
                    if (  (record.at(5).toInt(&ok,16)) == 0x0 ) {
                        AttrDesc ="start packet";
                    }
                }
                else {
                    if ( (record.at(5).toInt(&ok,16)) & 0x8 ) {
                        AttrDesc ="ack";
                        if ( (record.at(5).toInt(&ok,16)) & 0x4 ) {
                            b6param ="negative";
                        }
                    }
                    else {
                        AttrDesc ="cmd";
                        if ( ( (record.at(5).toInt(&ok,16)) & 0x4 ) && (record.at(5).toInt(&ok,16) & 0x2 ) ) {
                            b6param = "need ack<br>cmd with params";
                        }
                        if ( !( (record.at(5).toInt(&ok,16)) & 0x4 ) && (record.at(5).toInt(&ok,16) & 0x2 ) ) {
                            b6param = "no need ack<br>cmd with params";
                        }
                        if ( ( (record.at(5).toInt(&ok,16)) & 0x4 ) && !(record.at(5).toInt(&ok,16) & 0x2 ) ) {
                            b6param = "need ack<br>cmd without params";
                        }
                        if ( !( (record.at(5).toInt(&ok,16)) & 0x4 ) && !(record.at(5).toInt(&ok,16) & 0x2 ) ) {
                            b6param = "no need ack<br>cmd without params";
                        }
                    }

                }


                out << "<tr> <td class=\""+background+"\">" << record[0] <<"</td>"
                       "<td class=\""+background+"\">"      << record[1] <<"</td>"
                       "<td class=\""+background+"\">"      << record[2] <<"</td>"
                       "<td class=\""+background+"\">"      << record[3] <<"</td>"
                       "<td class=\""+background+"\">"      << record[4] <<"</td>"
                       "<td class=\""+background+"\">"      << QString("0x%1").arg(record.at(5).toInt(&ok,16),0,16) <<"<br>("+AttrDesc+") <br>("+b6param+")</td>"
                       "<td class=\""+background+"\">"      << FullDescriptionParams( record[1], record[2], record[5], record[6] ) <<"</td> </tr>";

            }
            else {
                out << "<tr>"
                       "<td class=\"brd_header\"> <strong>" << record[0] << " </strong></td>"
                       "<td class=\"brd_header\"> <strong>" << record[1] << " </strong></td>"
                       "<td class=\"brd_header\"> <strong>" << record[2] << " </strong></td>"
                       "<td class=\"brd_header\"> <strong>" << record[3] << " </strong></td>"
                       "<td class=\"brd_header\"> <strong>" << record[4] << " </strong></td>"
                       "<td class=\"brd_header\"> <strong>" << record[5] <<"  </strong></td>"
                       "<td class=\"brd_header\"> <strong>" << record[6] <<"  </strong></td></tr>";
            }
            i++;
        }
        out<<"</table></center></font></body></html>";
    }

    file.close();
    return ( out.status() ==QTextStream::Ok );
}



