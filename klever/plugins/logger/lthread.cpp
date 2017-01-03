#include "lthread.h"

void LThread::run()
{
    bool flag = true;

    while(flag) {

        if (!m_logList.isEmpty()) {
            logPacket pkt = takeItemFromlogList();
            QString type;
            if (pkt.type == MESSAGE_ERROR) {
                type = "<font color='red'><b>[Ошибка]</b></font>";
            }
            if (pkt.type == MESSAGE_WARNING){
                type = "<font color='orange'><b>[Предупреждение]</b></font>";
            }
            if (pkt.type == MESSAGE_INFO) {
                type = "<font color='blue'><b>[Информация]</b></font>";
            }

            QString txt = QString("%1 <b>%2</b> <i>%3</i>  --> %4")
                                    .arg(type)
                                    .arg(pkt.ptr->objectName())
                                    .arg(pkt.datetime)
                                    .arg(pkt.txt);

            emit sendMessage(txt);
        }
        msleep(100);
    }
}

LThread::LThread()
{

}
