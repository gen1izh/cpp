#ifndef MYSQL_DATABASE_API_H
#define MYSQL_DATABASE_API_H
#include <QString>
#include <QtSql>
#include <QObject>

/*!
 * \brief Класс обеспечивающий работу с БД mysql
 */
class MySQLDataBaseApi : public QObject
{

  Q_OBJECT

  MySQLDataBaseApi(){
    setObjectName(tr("Api работы с БД"));
  }

  MySQLDataBaseApi(const MySQLDataBaseApi& root);

  MySQLDataBaseApi& operator=(const MySQLDataBaseApi&);

  /*!
   * \brief Функция запроса
   * \param[in] query - запрос
   * \return
   */
  bool queryExec(QString query, QString quename);

protected:
  /*!
   * \brief Дескриптор БД
   */
  QSqlDatabase _db;

public:

  static MySQLDataBaseApi& instance();

  /*!
   * \brief Указатель объекта запроса
   */
  QHash<QString, QSqlQuery *> _query;

  /*!
   * \brief Возвращает указатель на объект запроса
   * \return
   */
  QHash<QString, QSqlQuery *> query() { return _query; }

  /*!
   * \brief records
   * \return
   */
  QSqlRecord records(QString name) { return _query[name]->record(); }

  /*!
   * \brief Проверка текущего соединения на корректность
   * \return
   */
  bool isConnectionsToDatabaseValid(QString db, QString mysqlConnectionDescriptor);

  /*!
   * \brief Проверка на существование БД
   * \return признак сущестования БД
   */
  bool isDatabaseExisting(QString name, QString connectionName, QString quename);

  /*!
   * \brief Проверка на существование таблицы в БД
   * \param[in] table имя таблицы
   * \return признак сущестования таблицы
   */
  bool isTableInDatabaseExisting(QString dbname, QString connectionName, QString tablename, QString quename);

  /*!
   * \brief Создание БД
   * \return возвращает результат создания БД
   */
  bool createDatabase(QString name, QString connectionName, QString quename);

  /*!
   * \brief Создание таблицы
   * \param[in] table имя таблицы
   * \param[in] structure структура таблицы
   * \return возвращает результат создания таблицы
   */
  bool createTable(QString dbname, QString connectionName, QString tablename, QString structure, QString quename);

  /*!
   * \brief Удаление таблицы
   * \param[in] table имя таблицы
   * \return возвращает результат удаления таблицы
   */
  bool dropTable(QString dbname, QString connectionName, QString table, QString quename);

  /*!
   * \brief Обзор всех таблиц В БД
   * \return возвращает результат обзора таблиц
   */
  bool showTables(QString dbname, QString connectionName, QString quename);

  /*!
   * \brief Добавление записи в таблицу
   * \param[in] table имя таблицы
   * \param[in] structure структура записи в таблице
   * \return
   */
  bool insertIntoTable(QString dbname, QString connectionName, QString tablename, QString structure, QString quename);


  /*!
   * \brief Показать все данные из таблицы
   * \return
   */
  bool selectAllDataFromTable(QString dbname, QString connectionName, QString tablename/*, QSqlQuery *query*/, QString quename);

  /*!
   * \brief Удаление записи по индексу
   * \param[in] table название таблицы
   * \param[in] id идентификатор записи
   * \return
   */
  bool deleteRecordById(QString dbname, QString connectionName, QString tablename, int id, QString quename);

  /*!
   * \brief Закрытие сессии работы с БД
   */
  void disconnect();

  /*!
   * \brief Возвращает последний идентификатор
   * \param[in] id - идентификатор
   * \return
   */
  bool lastId(QString dbname, QString connectionName, QString tablename, int &id, QString quename);

  /*!
   * \brief Произвольный запрос
   * \param[in] query - запрос
   * \return
   */
  bool sqlquery(QString dbname, QString connectionName, QString query, QString quename);

  /*!
   * \brief Возвращает дескриптор на БД
   * \return
   */
  QSqlDatabase &getDescriptor(QString dbname, QString connectionName) {
    if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
      qDebug() << "error descriptor";
    }
    return _db;
  }



};

#endif // MYSQL_DATABASE_API_H
