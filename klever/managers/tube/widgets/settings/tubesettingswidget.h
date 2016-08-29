#ifndef tube_SETTINGS_H
#define tube_SETTINGS_H

#include <QWidget>
#include <QTableWidget>
#include <QTimer>

class TubeSettings : public QWidget
{
  Q_OBJECT

  void createConnectors();

  QTableWidget *_table;
  QTimer       *_timer;

public:
  explicit TubeSettings(QWidget *parent = 0);

public slots:
  void updateTable();
signals:

};

#endif // tube_SETTINGS_H

