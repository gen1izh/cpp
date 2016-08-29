#ifndef TEMPLATEAPIWRAPPER_H
#define TEMPLATEAPIWRAPPER_H


#include <QObject>

// Подключение заглушки сообщений лога
#include <library/setupApi/module.h>




/*!
  * Обертка API интерфейса функций для ШАБЛОН
  */
class TemplateApiWrapper : public QObject
{
    Q_OBJECT
  public:
    /*!
     * \brief Конструктор обертки для работы с прошивкой ШАБЛОН
     */
    TemplateApiWrapper();
    ~TemplateApiWrapper();


  private:



  public slots:

};

#endif // TEMPLATEAPIWRAPPER_H
