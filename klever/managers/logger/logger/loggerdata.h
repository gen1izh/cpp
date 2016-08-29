#ifndef LOGGERDATA_H
#define LOGGERDATA_H

#include <QObject>
#include <QMutex>
#include <QFile>
#include <QWidget>
#include <QTableView>
#include <QModelIndex>
#include <QSortFilterProxyModel>
#include <QAction>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDateTime>
#include <QTextStream>
#include <QHeaderView>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QMenu>
#include <QAbstractTableModel>
#include <QList>
#include <QMap>
#include <QDateTime>
#include <QIcon>
#include <QFileDialog>
#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QHeaderView>
#include <QDateTimeEdit>
#include <QItemDelegate>
#include <QtGui>
#include <QSettings>
#include <QDir>
#include <QtConcurrent/QtConcurrent>
#include <QProgressBar>

/*!
 * \details Количество записей на странице. Это необходимо для вывода сообщений в
 * представления жураналов и просмотрщику журналов.
 * \note Необходимо в будущем либо вынести этот параметр в настройки,
 * либо оставить так как есть. Если после совещания будет не принципиально
 * какой будет эта величина, то оставить так как есть.
 */

#define PAGE_SIZE 30 // количество записей на одной странице

/*******************************************************************************
 *                                Типы данных
 *  Типы сообщений, структура сообщения, биты фильтрации, карта источников событий.
 *******************************************************************************/

/*!
 * \brief Типы журналируемых сообщений
 * \details Существуют ошибочные, информационные сообщения и сообщения предупреждений.
 */
enum MESSAGE_TYPES {
  ALL_MESSAGES,         /*! Все типы сообщений */
  ERROR_MESSAGES,       /*! Ошибочное сообщение */
  INFORMATION_MESSAGES, /*! Информационное сообщение */
  WARNING_MESSAGES      /*! Сообщение предупреждения */
};

/*!
 * \brief Коды состояний
 * \todо Актуализировать список  кодов состояний
 */
enum CODE_STATES {
  SUCCESSFUL = 0,             /*! Операция успешно выполнена */

  FILE_OPEN_ERROR,            /*! Ошибка при открытии файла */
  FILE_DESCRIPTOR_ERROR,      /*! Ошибка дескриптора файла */
  FILE_PUSH_ERROR,            /*! Ошабка записи записи в хранилище */
  FILE_CLOSE_ERROR            /*! Ошибка закрытия файла */
};

/*!
 * \brief Структура журналируемого сообщения
 */
typedef struct {
  MESSAGE_TYPES type;          /*! Тип сообщения */
  QDateTime     dtime;         /*! Время журналирования события */
  QString       sourceName;    /*! Источник события */
  QString       text;          /*! Сообщение события */
} messageStructure;

/*!
 *  \brief Флаги фильтрации сообщений по типу
 */
enum MESSAGE_TYPES_FILTR_FLAG {
  NO_MESSAGE_FILTRING   = 0x7, /*! Не фильтровать сообщения */
  INFO_MESSAGE_FILTRING = 0x1, /*! Фильтрация только информационных сообщений */
  WARN_MESSAGE_FILTRING = 0x2, /*! Фильтрация только сообщений предупреждения */
  ERR_MESSAGE_FILTRING  = 0x4  /*! ФИльтрация ошибочных сообщений */
};


/*!
 *  \brief Объявление флагов фильтрации по типу.
 */
Q_DECLARE_FLAGS(MESSAGE_TYPES_FILTR_FLAGS, MESSAGE_TYPES_FILTR_FLAG)
Q_DECLARE_OPERATORS_FOR_FLAGS(MESSAGE_TYPES_FILTR_FLAGS)


/*!
 *  \brief Карта источников сообщений.
 *  \note  Необходима для  фильтрации по источнику сообщения.
 */
typedef
  QMap< QString, bool > MessagesSourcesMap;


#endif // LOGGERDATA_H
