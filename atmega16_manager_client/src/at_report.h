#ifndef AT_REPORT_H
#define AT_REPORT_H
#include <QtGui>
#include <prt/cmd_packet.h>

struct ATMC_ReportItem{
  bool            is_ok;
  QString         DataTime;
  QString         Command;
  QString         DevType;
  QString         DevMinor;
  QString         Dump;
  QString         Desc;
  at_cmd_packet   Answer;
};

class ATMC_Report {
  public:
    static ATMC_Report *Instance();
    QList<QTreeWidgetItem *> Repaint();
    QString GetDataTime( int num );
    QString GetCommandName( int num );
    QString GetDevType( int num );
    QString GetDevMinor( int num );
    QString GetDump( int num );
    QString GetDescription( int num );
    int GetListSize();
    void AddItem( ATMC_ReportItem r );

  private:
    QList<ATMC_ReportItem> reportItemList;
    static ATMC_Report *instance;

  protected:
    ATMC_Report();
};

#endif // AT_REPORT_H
