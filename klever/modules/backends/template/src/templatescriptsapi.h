#ifndef TEMPLATESCRIPTSAPI_H
#define TEMPLATESCRIPTSAPI_H

#include <QtWidgets>
#include <QObject>
#include <QTextCodec>

#include "templatemodule.h"



class TemplateScriptsApi : public QObject {

    Q_OBJECT

  /*!
   * \brief Внутренний указатель на модуль, для вызова функций библиотеки
   */
  TemplateModule *_dev;

  public:
    explicit TemplateScriptsApi( QObject *parent = 0, TemplateModule *dev = NULL );

  signals:

  public slots:



  /*!
   *  \brief   Функция возвращает список функций АПИ модуля.
   */
    QStringList getPromptingMessages();

};

#endif // TEMPLATESCRIPTSAPI_H
