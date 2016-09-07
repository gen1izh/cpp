#include "mysqldatabaseapi.h"
#include <frameWork/cveManager.h>
#include <frameWork/gui/cvegui.h>

#include <library/loggerapi/loggerapi.h>

using namespace Library::LoggerApi;

/*
 * Инстанцирование объекта api функций для работы с БД
 */
MySQLDataBaseApi &MySQLDataBaseApi::instance() {
  static MySQLDataBaseApi singleObject;
  return singleObject;
}

/*
 * Проверка состояния текущего запроса
 */
bool MySQLDataBaseApi::queryExec(QString query, QString quename) {

  static int errCounter = 0;

  if (!_query.contains(quename)) {
    _query[quename] = new QSqlQuery(_db);
    qDebug().noquote() << QString("Запрос с ключем(%1) отсутствует!").arg(quename);
  }

  if (!_query[quename]->exec(query)) {
    logWarning(this, QString("Запрос (%1) не выполнен.").arg(query));
    logWarning(this, QString("Имя БД: %1").arg(_db.databaseName()));

    logWarning(this, QString("Хост: %1").arg(_db.hostName()));
    logWarning(this, QString("Порт: %1").arg(_db.port()));
    logWarning(this, QString("Имя пользователя: %1").arg(_db.userName()));

    logWarning(this, QString("Ошибка запроса: %1").arg(_query[quename]->lastError().text()));

    if (!_query[quename]->isActive()) {
      logWarning(this, QString("Запрос не активен!"));
    }

    if (!_query[quename]->isValid()) {
      logWarning(this, QString("Запрос не валиден!"));
    }

    if ((_db.open()) && (errCounter<10)) {
      errCounter++;
      queryExec(query, quename);
    }
    else {
      logWarning(this, QString("Не переоткрывается БД: %1").arg(_db.lastError().text()));
    }

    return false;
  }

  return true;
}

/*
 * Проверка текущего соединения на корректность
 */
bool MySQLDataBaseApi::isConnectionsToDatabaseValid(QString db, QString mysqlConnectionDescriptor)
{

  _db = QSqlDatabase::database(mysqlConnectionDescriptor);

  if(!_db.isValid()) {
    // Добавляем в хеш стандартную БД
    // Это необходимо для подключения к БД и создания других БД
    _db = QSqlDatabase::addDatabase("QMYSQL", mysqlConnectionDescriptor);
    _db.setDatabaseName("mysql");
    _db.setHostName("127.0.0.1");
    _db.setPassword("476");
    _db.setUserName("root");
    _db.setPort(3306);
    if (!_db.open()) {
      qDebug().noquote() << "Не удалось открыть БД!";
    }
  }

  if (_db.isOpen()) {
    if (_db.databaseName() != db) {
      qDebug().noquote() << "Текущая имя БД: " <<_db.databaseName() << " Устанавливаемая БД: " << db;

      logInfo(this, QString("Текущая имя БД: %1 Устанавливаемая БД: %2 (%3)")
              .arg(_db.databaseName())
              .arg(db)
              .arg(_db.lastError().text()));

//      _db.close();

      // TODO Очиститка всех объектов запросов
//      QHashIterator<QString, QSqlQuery *> i(_query);
//      while (i.hasNext()) {
//          i.next();
//          delete i.value();
//      }
//      _query.clear();

      _db.setDatabaseName(db);
      _db.open();

      if (_db.isOpen()) {
        logInfo(this, QString("БД: %1 успешно открыта").arg(db));
      }
      else {
        logInfo(this, QString("БД: %1 не открыта (%2)")
                .arg(db)
                .arg(_db.lastError().text()));
      }
    }
  }
  else {
    qDebug().noquote() << "БД не открыта" << _db.lastError().text();
    _db.setDatabaseName(db);
    _db.open();

//    if (_query == NULL) {
//      _query = new QSqlQuery(_db);
//    }

    if (_db.isOpen()) {
      logInfo(this, QString("БД: %1 успешно открыта").arg(db));
    }
    else {
      logInfo(this, QString("БД: %1 не открыта (%2)")
              .arg(db)
              .arg(_db.lastError().text()));
    }
  }


  if (!_db.isDriverAvailable("QMYSQL")) {
    qDebug().noquote() << QString("Драйвер Mysql не доступен (%1)! ").arg(_db.lastError().text());
    logError(this, QString("Драйвер Mysql не доступен (%1)! ").arg(_db.lastError().text()));
    return false;
  }

  if (!_db.isOpen()) {
    qDebug().noquote() << QString("Дескриптор на БД закрыт, либо недоступен (%1)! ").arg(_db.lastError().text());
    logError(this, QString("Дескриптор на БД закрыт, либо недоступен (%1)! ").arg(_db.lastError().text()));
    return false;
  }

  if (_db.isOpenError()) {
    qDebug().noquote() << QString("Ошибка открытия сессии работы с БД (%1)! ").arg(_db.lastError().text());
    logError(this, QString("Ошибка открытия сессии работы с БД (%1)! ").arg(_db.lastError().text()));
    return false;
  }

  if (!_db.isValid()) {
    qDebug().noquote() << QString("Дескриптор сломан (%1)! ").arg(_db.lastError().text());
    logError(this, QString("Дескриптор сломан (%1)! ").arg(_db.lastError().text()));
    return false;
  }

  return true;
}

/*
 * Закрываем дескриптор
 */
void MySQLDataBaseApi::disconnect()
{
//  static_cast<QSqlDatabase>(_db).close();
}


/*
 * Проверка на существование БД
 */
bool MySQLDataBaseApi::isDatabaseExisting(QString name, QString connectionName, QString quename) {

  if (!isConnectionsToDatabaseValid(name, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("show databases;"), quename);

    if (result) {
      QSqlRecord rec = _query[quename]->record();
      int databases = rec.indexOf("Database");
      while (_query[quename]->next()) {
        QString databaseName = _query[quename]->value(databases).toString();
        if (databaseName == name) {
          return true;
        }
      }
      logWarning(this, QString("БД %1 не существует!").arg(name));
      return false;
    }
    else {
      logError(this, QString("Не удалось выполнить операцию SHOW DATABASES !"));
      return false;
    }

  }

  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}

/*
 * Создание БД
 */
bool MySQLDataBaseApi::createDatabase(QString name, QString connectionName, QString quename) {

  if (!isConnectionsToDatabaseValid("mysql", connectionName)) {
    return false;
  }

  // Если БД не существует, то подключаемся к стандартной БД
  // и через это подключение создаем БД которая требуется
  if (_db.isOpen()) {
    bool result = queryExec(QString("CREATE DATABASE IF NOT EXISTS %1 DEFAULT CHARACTER SET UTF8;").arg(name), quename);
    if (result==false) {
      logError(this, QString("Не получилось создать БД"));
      return false;
    }

    return true;
  }

  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}

/*
 * Проверка на сущестование таблицы
 */
bool  MySQLDataBaseApi::isTableInDatabaseExisting(QString dbname, QString connectionName, QString tablename, QString quename) {

  if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("use %1;").arg(dbname), quename);

    if (result) {
      bool res = queryExec(QString("show tables;"), quename);

      if (res ) {
        QSqlRecord rec = _query[quename]->record();
        int databases = rec.indexOf(QString("Tables_in_%1").arg(dbname));
        if (databases!=-1) {
          while (_query[quename]->next()) {
            QString name = _query[quename]->value(databases).toString();
            if (tablename == name) {
              return true;
            }
          }
          logInfo(this, QString("Таблица %1 не существует в БД %2 !").arg(tablename).arg(dbname));
          return false;
        }
        else {
          logInfo(this, QString("Таблиц %1 не существует в БД %2 !").arg(tablename).arg(dbname));
          return false;
        }
      }
    }
    else {
      logError(this, QString("Не удалось подключиться к БД %1(%2) !").arg(dbname).arg(_db.lastError().text()));
      return false;
    }
  }

  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}


/*
 * Создание таблицы
 */
bool MySQLDataBaseApi::createTable(QString dbname, QString connectionName, QString tablename, QString structure, QString quename) {

  if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("use %1;").arg(dbname), quename);
    if (result) {
      bool res = queryExec(QString("CREATE TABLE IF NOT EXISTS %1 %2;").arg(tablename).arg(structure), quename);
      if (res ==false) {
        logError(this, QString("Не получилось создать таблицу %1 в БД %2 !")
                       .arg(tablename).arg(dbname));
        return false;
      }
      else {
        logInfo(this, QString("Создал таблицу %1 в БД %2 !")
                       .arg(tablename).arg(dbname));
        return true;
      }
    }
    else {
      logError(this, QString("Не удалось подключиться к БД %1(%2) !").arg(dbname).arg(_db.lastError().text()));
      return false;
    }
  }

  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}


/*
 * Обзор всех таблиц В БД
 */
bool MySQLDataBaseApi::showTables(QString dbname, QString connectionName, QString quename) {

  if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("use %1;").arg(dbname), quename);
    if (result) {
      bool res = queryExec(QString("show tables;"), quename);
      return res;
    }
    else {
      logError(this, QString("Не удалось подключиться к БД %1(%2) !").arg(dbname).arg(_db.lastError().text()));
      return false;
    }
  }

  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}


/*
 *  Удаление таблицы
 */
bool MySQLDataBaseApi::dropTable(QString dbname, QString connectionName, QString tablename, QString quename) {

  if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("use %1;").arg(dbname), quename);
    if (result) {
      bool res = queryExec(QString("drop table %1;").arg(tablename), quename);
      if (res ==false) {
        logError(this, QString("Не получилось удалить таблицу %1 в БД %2 !")
                       .arg(tablename).arg(dbname));
        return false;
      }
      else {
        return true;
      }
    }
    else {
      logError(this, QString("Не удалось подключиться к БД %1(%2) !").arg(dbname).arg(_db.lastError().text()));
      return false;
    }
  }

  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}

/*
 * Показать все данные из таблицы
 */
bool MySQLDataBaseApi::selectAllDataFromTable(QString dbname, QString connectionName, QString tablename, QString quename) {

  if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("use %1;").arg(dbname), quename);
    if (result) {
      bool res = queryExec(QString("select * from %1;").arg(tablename), quename);
      if (res ==false) {
        logError(this, QString("Не удалось получить данные из таблицы %1 БД %2 (%3) !")
                       .arg(tablename).arg(dbname).arg(_db.lastError().text()));
        logError(this, QString("Имя соединения: %1").arg(connectionName));

        _db = QSqlDatabase::database(connectionName);

        if(!_db.isValid()) {
          logError(this, QString("БД с таким именем не валидна(%1)").arg(_db.lastError().text()));
        }

        return false;
      }
      else {
        return true;
      }
    }
    else {
      logError(this, QString("Результат исполнения запроса %1 (%2) !")
               .arg(QString("use %1;")
               .arg(dbname))
               .arg(_query[quename]->lastError().text()));
      return false;
    }
  }

  logError(this, QString("Сессия работы с менеджером БД не открыта (%1)!").arg(_db.lastError().text()));

  return false;
}


/*
 * Добавление строки в таблицу
 */
bool MySQLDataBaseApi::insertIntoTable(QString dbname, QString connectionName, QString tablename, QString structure, QString quename) {

  if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("use %1;").arg(dbname), quename);

    if (result) {
      bool res = queryExec(QString("INSERT INTO %1 VALUES %2;").arg(tablename).arg(structure), quename);

      if (res==false) {
//        logError(this, QString("Не получилось вставить данные в таблицу %1 в БД %2 !")
//                       .arg(tablename).arg(dbname));
        return false;
      }
      else {
        return true;
      }
    }
    else {
      logError(this, QString("Не удалось подключиться к БД %1(%2) !").arg(dbname).arg(_db.lastError().text()));
      return false;
    }
  }

  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}



/*
 * Получение последнего добавленного индекса
 * TODO:
 */
bool MySQLDataBaseApi::lastId(QString dbname, QString connectionName, QString tablename, int &id, QString quename) {
  bool ok;

  if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("use %1;").arg(dbname), quename);
    if (result) {
      bool res = queryExec(QString("select * from %1 order by id desc limit 1;").arg(tablename), quename);
      if (res ==false) {
        logError(this, QString("Не получилось получить последний ID из таблицу %1 в БД %2 !")
                       .arg(tablename).arg(dbname));
        return false;
      }
      else {
        id = -1;
        QSqlRecord rec = _query[quename]->record();
        int lastid = rec.indexOf("id");
        while (_query[quename]->next()) {
          id = _query[quename]->value(lastid).toInt(&ok);
        }
        return true;
      }
    }
    else {
      logError(this, QString("Не удалось подключиться к БД %1(%2) !").arg(dbname).arg(_db.lastError().text()));
      return false;
    }
  }

  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}



/*
 * Произвольный запрос
 */
bool MySQLDataBaseApi::sqlquery(QString dbname, QString connectionName, QString query, QString quename) {

  if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("use %1;").arg(dbname), quename);
    if (result) {
      bool res = queryExec(query, quename);
      if (res ==false) {
        logError(this, query);
        logError(this, QString("Не удалось выполнить запрос (%1)!").arg(_query[quename]->lastError().text()));
        return false;
      }
      else {
        return true;
      }
    }
    else {
      logError(this, QString("Не удалось подключиться к БД %1(%2) !").arg(dbname).arg(_db.lastError().text()));
      logError(this, QString("Имя соединения: %1").arg(connectionName));

      _db = QSqlDatabase::database(connectionName);

      if(!_db.isValid()) {
        logError(this, QString("БД с таким именем не валидна(%1)").arg(_db.lastError().text()));
      }
      return false;
    }
  }
  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}


/*
 * Удаление записи из таблицы
 */
bool MySQLDataBaseApi::deleteRecordById(QString dbname, QString connectionName, QString tablename, int id, QString quename) {

  if (!isConnectionsToDatabaseValid(dbname, connectionName)) {
    return false;
  }

  if (_db.isOpen()) {
    bool result = queryExec(QString("use %1;").arg(dbname), quename);
    if (result) {
      bool res = queryExec(QString("delete from %1 where id=%2;").arg(tablename).arg(id), quename);
      if (res == false) {
        logError(this, QString("Не получилось удалить запись под ID=%1 из таблицу %2 в БД %3 !")
                       .arg(id).arg(tablename).arg(dbname));
        return false;
      }
      else {
        return true;
      }
    }
    else {
      logError(this, QString("Не удалось подключиться к БД %1(%2) !").arg(dbname).arg(_db.lastError().text()));
      return false;
    }
  }

  logError(this, QString("Сессия работы с менеджером БД не открыта!"));

  return false;
}

