#include "templatescriptsapi.h"

/*
 * Конструктор скриптов
 */
TemplateScriptsApi::TemplateScriptsApi(QObject *parent, TemplateModule *dev ) :
  QObject(parent) {
  QTextCodec::setCodecForLocale  ( QTextCodec::codecForName("UTF-8") /*langcodec*/ );
  this->setObjectName( tr(" Модуль скриптов ") );
  _dev = dev;
}


/*
 * Функция возвращает список функций АПИ модуля.
 */
QStringList TemplateScriptsApi::getPromptingMessages() {
  QStringList sl;

  return sl;
}



