#include "systemoperations.h"
#include <frameWork/cve.h>


/*
 * Печать(добавление) текста в файл (в кодировке Koi8r).
 */
void SystemOperations::_printKoi8r_a(QString txt) {
  QFile file( _fileName );
  if ( !file.open( QIODevice::Append | QIODevice::Text ) ) {
    return;
  }
  QTextStream out( &file );
  out.setCodec( "koi8-r" );
  out << txt << "\n";
}

/*
 * Печать(создание с перезаписью) текста в файл (в кодировке Koi8r).
 */
void SystemOperations::_printKoi8r_w(QString txt) {
  QFile file( _fileName );
  if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) ) {
    return;
  }
  QTextStream out( &file );
  out.setCodec( "koi8-r" );
  out << txt << "\n";
}

/*
 * Печать(добавление) текста в файл (в кодировке utf-8).
 */
void SystemOperations::_printUtf8_a(QString txt) {
  QFile file( _fileName );
  if ( !file.open( QIODevice::Append | QIODevice::Text ) ) {
    return;
  }
  QTextStream out( &file );
  out.setCodec( "utf-8" );
  out << txt << "\n";
}

/*
 * Печать(создание с перезаписью) текста в файл (в кодировке utf-8).
 */
void SystemOperations::_printUtf8_w(QString txt) {
  QFile file( _fileName );
  if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) ) {
    return;
  }
  QTextStream out( &file );
  out.setCodec( "utf-8" );
  out << txt << "\n";
}

/*
 * Cоздание с перезаписью текстового файла (в кодировке Koi8r).
 */
void SystemOperations::createKoi8rFile(QString txt) {
  _printKoi8r_w( txt );
}

/*
 * Cоздание с перезаписью текстового файла (в кодировке Utf8).
 */
void SystemOperations::createUtf8File(QString txt) {
  _printUtf8_w( txt );
}


/*
 * Установка имени файла, с которым будет производиться работа в скрипте.
 */
void SystemOperations::setFileName(QString filename) {
  // Проверяем включен ли модуль. Чтение настроек.
//  MainSetupApi  mainsetup;
//  // Проверка наличия пе
//  mainsetup.checkMainParam(QString("Variables"), QString("/sessionPath"), QString(""));
//  QString sessionPath = mainsetup.getMainParam(QString("Variables"), QString("/sessionPath"));

  QString sessionPath =Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));

  _fileName = QString("%1/%2")
      .arg(sessionPath)
      .arg(filename);

  SysLibrary::UtilsLibrary pathChecker;
  QFileInfo f;
  f.setFile(_fileName);
  QString p = f.absolutePath();
  pathChecker.checkFolder(p);
}

/*
 * Запись в файл произвольный текст(в кодировке Koi8r).
 */
void SystemOperations::printKoi8rSomeText(QString txt) {
  _printKoi8r_a( txt );
}

/*
 * Запись в файл произвольный текст(в кодировке Utf8).
 */
void SystemOperations::printUtf8SomeText(QString txt) {
  _printUtf8_a( txt );
}


void SystemOperations::replaceText(QString origin, QString replacement) {

  QByteArray fileData;
  QFile file(_fileName);

  if (!file.open(QIODevice::ReadWrite))
    return;


  fileData = file.readAll();

  QString text(fileData);


  text.replace(origin, replacement);

  file.resize(0);


  file.seek(0);
  file.write(text.toUtf8());

  file.close();
}


bool SystemOperations::containsText(QString str)
{
  QByteArray fileData;
  QFile file(_fileName);

  if (!file.open(QIODevice::ReadWrite))
    return false;


  fileData = file.readAll();

  QString text(fileData);

  file.close();

  return text.contains(str);
}
