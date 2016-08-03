#include "at_report.h"
#include "at_manager_client.h"

ATMC_Report *ATMC_Report::instance = 0;

ATMC_Report::ATMC_Report() {
}

ATMC_Report *ATMC_Report::Instance() {
  if ( instance == 0 )
    instance = new ATMC_Report();
  return instance;
}

QList<QTreeWidgetItem *> ATMC_Report::Repaint() {
  QStringList columns;
  QList<QTreeWidgetItem *> items;
  QTreeWidgetItem *item = NULL;
  QTreeWidgetItem *child =NULL;

  for ( int i = 0; i < GetListSize(); i++ ) {
    columns.clear();
    columns << GetDataTime(i);

    item = new QTreeWidgetItem( columns );
    item->setFlags( item->flags() | Qt::ItemIsEditable );
    columns.clear();
    columns << "" << GetDevType(i) << GetCommandName(i)
            << GetDump(i) << GetDescription(i);
    child = new QTreeWidgetItem(columns);
    item->addChild(child);

    items.append(item);
    item->setExpanded(false);
  }
  return items;
}

QString ATMC_Report::GetDataTime(int num) {
  return reportItemList.at( num ).DataTime;
}

int ATMC_Report::GetListSize() {
  return reportItemList.size();
}

void ATMC_Report::AddItem(ATMC_ReportItem r) {
  reportItemList.append( r );
}

QString ATMC_Report::GetDescription(int num) {
  return reportItemList.at( num ).Desc;
}

QString ATMC_Report::GetDump(int num) {
  return reportItemList.at( num ).Dump;
}

QString ATMC_Report::GetDevMinor(int num) {
  return reportItemList.at( num ).DevMinor;
}

QString ATMC_Report::GetDevType(int num) {
  return reportItemList.at( num ).DevType;
}

QString ATMC_Report::GetCommandName(int num) {
  return reportItemList.at( num ).Command;
}
