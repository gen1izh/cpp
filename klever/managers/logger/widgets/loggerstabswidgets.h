#ifndef LOGGERSTABSWIDGETS_H
#define LOGGERSTABSWIDGETS_H

#include <QWidget>
#include <QGridLayout>
#include <QTabWidget>

#include "../logger/filestorage.h"
#include "../logger/logger.h"

class LoggersTabsWidgets : public QWidget
{
  Q_OBJECT

  /*!
   * \brief Компоненты модуля журналирования
   */
  QList<FileStorage*> _dataStorages;

  /*!
   * \brief Хеш журналов приложения
   */
  QHash<int, Logger*> _loggers;

public:
  explicit LoggersTabsWidgets(QWidget *parent = 0);

  /*!
   * \brief Возвращает хеш логгеров
   * \return
   */
  QHash<int, Logger*> *loggers() { return &_loggers; }

  /*!
   * \brief Возвращает список хранилищ журналов
   * \return
   */
  QList<FileStorage*> storages() { return _dataStorages; }

  /*!
   * \brief Добавляет хранилище данных для журнала
   * \param[in] ds - хралище данных
   */
  void addDataStorage(FileStorage* ds) { _dataStorages.append(ds); }

  /*!
   * \brief Устанавливает журнал
   * \param[in] type - тип журнала
   * \param[in] l - указатель на журнал
   */
  void setLogger(int type, Logger* l) { _loggers[type] = l; }

signals:

public slots:
};

#endif // LOGGERSTABSWIDGETS_H
